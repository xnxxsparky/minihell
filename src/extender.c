/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypoulett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 01:26:12 by ypoulett          #+#    #+#             */
/*   Updated: 2025/09/02 19:28:25 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

int	handle_retcode(t_shell *shel, int *i)
{
	char	*code;
	int		len_a_add;

	len_a_add = 0;
	code = ft_itoa(shel->retcode);
	if (!code)
		return (0);
	(*i) += 2;
	len_a_add -= 2;
	len_a_add += ft_strlen(code);
	free(code);
	return (len_a_add);
}

static int	ret_fill(t_shell *shel, char *ret, int *i)
{
	char	*retcode;
	int		k;

	retcode = ft_itoa(shel->retcode);
	if (!retcode)
		return (2);
	k = 0;
	while (retcode[k])
		ret[(*i)++] = retcode[k++];
	free(retcode);
	return (2);
}

static int	dol_fill(t_shell *shel, char *token, char *ret, int *i)
{
	t_env	*env;
	char	*save;
	char	*name;
	int		k;
	int		j;

	j = 1;
	while (ft_isalnum(token[j]) || token[j] == '_')
		j++;
	save = token + 1;
	k = 0;
	name = ft_strndup(save, (token + j) - save);
	if (!name)
		return (j);
	env = env_finder(shel->env, name);
	if (env)
	{
		while (env->value[k])
			ret[(*i)++] = env->value[k++];
	}
	free(name);
	return (j);
}

static int	fill_dol(t_shell *shel, char *token, char *ret, int *i)
{
	if (token[1] && token[1] == '?')
		return (ret_fill(shel, ret, i));
	else
		return (dol_fill(shel, token, ret, i));
}

void	replace(t_shell *shel, char *token, char **token_fill)
{
	t_quotes	status;
	char		*ret;
	int			new_len;
	int			i;
	int			j;

	status = QUOTES_NONE;
	new_len = len_calc(shel, token);
	i = 0;
	j = i;
	ret = ft_calloc(new_len, sizeof(char));
	if (!ret)
		return ;
	while (token[j])
	{
		if (token[j] == '\'' || token[j] == '"')
			handle_status(&status, token[j]);
		if (token[j] == '$' && status != SIMPLE_QUOTES)
			j += fill_dol(shel, token + j, ret, &i);
		else
			ret[i++] = token[j++];
	}
	free(token);
	*token_fill = ret;
}
