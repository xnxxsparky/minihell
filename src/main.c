/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <bcausseq@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 00:01:58 by bcausseq          #+#    #+#             */
/*   Updated: 2025/09/02 20:28:15 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

void	env_join(char ***env_ar, t_env *env)
{
	t_env	*cur;
	char	**envp;
	int		len;
	int		i;

	if (*env_ar)
		free_spl((void **)*env_ar);
	cur = env;
	len = env_len(env);
	envp = ft_calloc(len + 1, sizeof(char *));
	if (!envp)
		return ;
	i = -1;
	while (++i < len)
	{
		envp[i] = ft_strjoin(cur->name, "=", 0, 0);
		if (!envp[i])
			return ;
		envp[i] = ft_strjoin(envp[i], cur->value, 1, 0);
		if (!envp[i])
			return ;
		cur = cur->next;
	}
	*env_ar = envp;
}

static void	sh_init(t_shell *shel, char **env)
{
	if (!env || !env[0] || !env[1] || !env[2] || !env[3])
		env_secure(&(shel->env));
	else
		shel->env = env_instantiate(env);
	if (!(shel->env))
		return ;
	sig_handler_classic();
	env_join(&(shel->env_ar), shel->env);
	if (!shel->env_ar)
		return ;
	prompt_initializer(shel, &(shel->prompt));
	shel->retcode = 0;
	if (!(shel->prompt))
		return ;
}

int	cmd_len_calc(t_token *cmd)
{
	t_token	*cur;
	int		ret;

	cur = cmd;
	ret = 1;
	while (cur)
	{
		if (cur->type == MST_PIPE)
			ret++;
		cur = cur->next;
	}
	return (ret);
}

static void	cmd_getter(t_shell *shel)
{
	reset_state();
	shel->cmd_user = readline(shel->prompt);
	if (is_line_valid(shel, shel->cmd_user) == false)
	{
		ft_fprintf(2, "Just learn to use Minihell plz :p\n");
		return ;
	}
	handle_input(shel);
	if (g_sig || lexer_handler(shel) != MS_PARSER_OKK)
		return ;
	buid_t_cmd(shel, &(shel->cmd_dec));
	if (!shel->cmd_dec || !shel->cmd_dec->cmd[0])
	{
		shel->retcode = 130;
		free(shel->cmd_user);
		free_tkn(&(shel->cmd));
		return ;
	}
	exec(shel);
	free(shel->cmd_user);
	free(shel->prompt);
	free_cmd_dec(&(shel->cmd_dec));
	free_tkn(&(shel->cmd));
	prompt_initializer(shel, &(shel->prompt));
}

int	main(int argc, char **argv, char **env)
{
	t_shell	shel;

	(void)argv;
	if (argc > 1)
	{
		ft_fprintf(2, "Actually, minishell doesn't take arguments"
			" MotherFucker\n");
		return (21);
	}
// 	ft_fprintf(1, "\e[1;1H\e[2J");
	ft_bzero(&shel, sizeof(t_shell));
	sh_init(&shel, env);
	while (1)
		cmd_getter(&shel);
	return (0);
}
