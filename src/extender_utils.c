/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extender_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <bcausseq@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 20:28:51 by bcausseq          #+#    #+#             */
/*   Updated: 2025/09/02 19:29:24 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

void	handle_status(t_quotes *status, char c)
{
	if (c == '\'')
	{
		if (*status == QUOTES_NONE)
			*status = SIMPLE_QUOTES;
		else if (*status == SIMPLE_QUOTES)
			*status = QUOTES_NONE;
	}
	else
	{
		if (*status == QUOTES_NONE)
			*status = DOUBLE_QUOTES;
		else if (*status == DOUBLE_QUOTES)
			*status = QUOTES_NONE;
	}
}

static int	handle_calc(t_shell *shel, char *token, int *i)
{
	t_env	*env;
	char	*save;
	char	*name;
	int		len_a_add;

	len_a_add = 0;
	save = token + (*i) + 1;
	(*i)++;
	len_a_add--;
	while (token[(*i)] && (ft_isalnum(token[(*i)]) || token[(*i)] == '_'))
	{
		(*i)++;
		len_a_add--;
	}
	name = ft_strndup(save, token + (*i) - save);
	if (!name || !*name)
		return (free(name), 0);
	env = env_finder(shel->env, name);
	free(name);
	if (env)
		len_a_add += ft_strlen(env->value);
	else
		len_a_add += ft_strlen(token);
	return (len_a_add);
}

int	len_calc(t_shell *shel, char *token)
{
	t_quotes	status;
	int			len_basique;
	int			len_a_add;
	int			i;

	status = QUOTES_NONE;
	len_basique = ft_strlen(token);
	len_a_add = 0;
	i = 0;
	while (token[i])
	{
		if (token[i] == '\'' || token[i] == '"')
			handle_status(&status, token[i]);
		if (token[i] == '$' && status != SIMPLE_QUOTES)
		{
			if (token[i + 1] && token [i + 1] == '?')
				len_a_add += handle_retcode(shel, &i);
			else
				len_a_add += handle_calc(shel, token, &i);
		}
		else
			i++;
	}
	return (len_basique + len_a_add + 1);
}
