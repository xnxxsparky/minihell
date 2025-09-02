/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qotes_remove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <bcausseq@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 21:19:17 by bcausseq          #+#    #+#             */
/*   Updated: 2025/09/02 19:39:51 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

static int	lenwoq(char *token)
{
	char	*tmp;
	int		ret;
	int		i;
	char	c;

	ret = 0;
	i = 0;
	while (token[i])
	{
		if (token[i] == '\'' || token[i] == '"')
		{
			c = token[i];
			i++;
			tmp = ft_strchr(token + i, c);
			ret += tmp - (token + i + 1);
			while (token[i] != c)
				i++;
		}
		i++;
		ret++;
	}
	return (ret);
}

static void	keep_good_ones(char *token, char *ret, int *i, int *j)
{
	char	*tmp;

	tmp = ft_strchr(token + (*i) + 1, token[*i]);
	(*i)++;
	if (!tmp)
		return ;
	while (token[*i] != *tmp)
	{
		ret[*j] = token[*i];
		(*i)++;
		(*j)++;
	}
}

static void	dead_quotes(char **token)
{
	char	*ret;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = lenwoq(*token);
	ret = ft_calloc(len + 1, sizeof(char));
	if (!ret)
		return ;
	while ((*token)[i])
	{
		if ((*token)[i] == '\'' || (*token)[i] == '"')
			keep_good_ones(*token, ret, &i, &j);
		else
		{
			ret[j] = (*token)[i];
			j++;
			i++;
		}
	}
	free(*token);
	*token = ret;
}

void	quotes_rm(t_token **cmd)
{
	t_token	*cur;

	cur = *cmd;
	while (cur)
	{
		if (cur->type == MST_WORD && !cur->expanded)
		{
			dead_quotes(&(cur->token));
			if (!cur->token)
				return ;
		}
		if (cur->type == MST_REDIR && !ft_strncmp(cur->token, "<<", 2)
			&& cur->next)
			cur->next->expanded = 1;
		cur = cur->next;
	}
	return ;
}
