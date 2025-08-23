/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <bcausseq@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 22:14:28 by bcausseq          #+#    #+#             */
/*   Updated: 2025/08/23 22:16:17 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

void	hist_adder(t_cmd *cmd_dec, int count, char *src)
{
	int			i;
	bool		add;

	i = -1;
	add = true;
	while (++i < count)
	{
		if (cmd_dec[i].name_fd_in
			&& ft_strncmp(cmd_dec[i].name_fd_in, ".heredoc", 8) == 0)
			add = false;
		if (cmd_dec[i].cmd[0] && ft_strcmp(cmd_dec[i].cmd[0], "exit") == 0)
		{
			if (cmd_dec[i].fd_in)
				ft_fprintf(cmd_dec[i].fd_in, "exit\n");
			else
				ft_fprintf(1, "exit\n");
		}
	}
	if (add == true)
		add_history(src);
}

void	close_all_fds(void)
{
	int	fds;

	fds = 2;
	while (++fds < 1024)
		close(fds);
}

void	close_all(t_cmd curr, int pipefd[2], int in, int out)
{
	if (pipefd[READ_SIDE] > 2)
		close(pipefd[READ_SIDE]);
	if (pipefd[WRITE_SIDE] > 2)
		close(pipefd[WRITE_SIDE]);
	if (curr.fd_in)
		close(curr.fd_in);
	if (curr.fd_out)
		close(curr.fd_out);
	if (in > 2)
		close(in);
	if (out > 2)
		close(out);
}

int	apply_builtins(t_shell *shel, int index)
{
	static t_op	funcs[8] = {
	{"exit", ft_exit}, {"pwd", ft_pwd},
	{"export", ft_export}, {"unset", ft_unset},
	{"env", ft_env}, {"cd", ft_cd}, {"echo", ft_echo},
	{0},
	};
	int			i;

	i = 0;
	signal(SIGPIPE, SIG_IGN);
	while (funcs[i].name)
	{
		if (ft_strcmp(shel->cmd_dec[index].cmd[0], funcs[i].name) == 0)
		{
			funcs[i].func(shel, index);
			return (0);
		}
		i++;
	}
	signal(SIGPIPE, SIG_DFL);
	return (1);
}

void	fauttoutfree_solo(t_shell *shel, bool need_exit, int index, bool redir)
{
	int	ex_cd;

	if (!shel->cmd_dec[index].path && redir == false && need_exit)
	{
		ex_cd = 127;
		if (shel->cmd_dec[index].cmd[0][0] != '$')
			ft_fprintf(2, "%s: command not found\n",
				shel->cmd_dec[index].cmd[0]);
	}
	else if (need_exit && redir == false)
	{
		ex_cd = 126;
		ft_fprintf(2, "minihell: %s: Permission denied\n",
			shel->cmd_dec[index].cmd[0]);
	}
	else
		ex_cd = 1;
	free_free(shel);
	if (need_exit)
		exit(ex_cd);
	exit(0);
}
