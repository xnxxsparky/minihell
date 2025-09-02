/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <bcausseq@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 01:56:13 by bcausseq          #+#    #+#             */
/*   Updated: 2025/09/02 01:57:32 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

bool	valid_xprt_name(char *test)
{
	bool	is_first;
	char	c;

	is_first = true;
	if (*test == '=')
		return (false);
	while (*test && *test != '=')
	{
		c = *test;
		if (is_first)
		{
			if (!ft_isalpha(c) && c != '_' && c != '?')
				return (false);
			is_first = false;
		}
		else
		{
			if (!ft_isalnum(c) && c != '_')
				return (false);
		}
		test++;
	}
	return (true);
}

t_env	*env_lstnew_xprt(char *name, char *value)
{
	t_env	*ret;

	ret = ft_calloc(1, sizeof(t_env));
	if (!ret)
		return (NULL);
	ret->name = ft_strdup(name);
	if (!ret->name)
	{
		free(ret);
		return (NULL);
	}
	if (!value || !*value)
		ret->value = "";
	else
	{
		ret->value = ft_strdup(value);
		if (!ret->value)
		{
			free(ret->name);
			free(ret);
			return (NULL);
		}
		ret->next = NULL;
	}
	return (ret);
}

t_env	**xprt_edit(t_env **env, char *name, char *val)
{
	t_env	*tmp;
	t_env	*newnode;

	if (!name)
		return (NULL);
	if (*env)
	{
		if (!val)
			val = "";
		tmp = *env;
		while (tmp)
		{
			if (ft_strcmp(tmp->name, name) == 0)
			{
				free(tmp->value);
				tmp->value = ft_strdup(val);
				return (env);
			}
			tmp = tmp->next;
		}
	}
	newnode = env_lstnew_xprt(name, val);
	env_lstadd_back(env, newnode);
	return (env);
}
