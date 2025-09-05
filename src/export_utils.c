/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <bcausseq@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 01:56:13 by bcausseq          #+#    #+#             */
/*   Updated: 2025/09/05 04:36:30 by bcausseq         ###   ########.fr       */
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

static bool	if_value(t_env *ret, char *value)
{
	ret->value = ft_strdup(value);
	if (!ret->value)
	{
		free(ret->name);
		free(ret);
		return (false);
	}
	ret->next = NULL;
	return (true);
}

static t_env	*env_lstnew_xprt(char *name, char *value, char *eq)
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
	if (!value)
	{
		if (!eq)
			ret->value = NULL;
		else
			ret->value = ft_calloc(1, 1);
	}
	else
	{
		if (!if_value(ret, value))
			return (NULL);
	}
	return (ret);
}

t_env	**xprt_edit(t_env **env, char *name, char *val, char *eq)
{
	t_env	*tmp;
	t_env	*newnode;

	if (!name)
		return (NULL);
	if (*env)
	{
		tmp = *env;
		while (tmp)
		{
			if (ft_strcmp(tmp->name, name) == 0)
			{
				if (tmp->value && *(tmp->value))
					free(tmp->value);
				tmp->value = ft_strdup(val);
				return (env);
			}
			tmp = tmp->next;
		}
	}
	newnode = env_lstnew_xprt(name, val, eq);
	env_lstadd_back(env, newnode);
	return (env);
}
