/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypoulett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 02:10:28 by ypoulett          #+#    #+#             */
/*   Updated: 2025/09/05 01:23:45 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

static t_env	*env_lstlast(t_env *env)
{
	if (!env)
		return (NULL);
	while (env->next)
		env = env->next;
	return (env);
}

t_env	*env_lstnew(char *name, char *value)
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
	ret->value = ft_strdup(value);
	if (!ret->value)
	{
		free(ret->name);
		free(ret);
		return (NULL);
	}
	ret->next = NULL;
	return (ret);
}

t_env	**env_addedit(t_env **env, char *name, char *val)
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
				if (tmp->value)
					free(tmp->value);
				tmp->value = ft_strdup(val);
				return (env);
			}
			tmp = tmp->next;
		}
	}
	newnode = env_lstnew(name, val);
	env_lstadd_back(env, newnode);
	return (env);
}

void	env_lstdelone(t_env **env, t_env *target)
{
	t_env	*curr;
	t_env	*prev;

	if (!env || !*env || !target)
		return ;
	curr = *env;
	prev = NULL;
	while (curr && curr != target)
	{
		prev = curr;
		curr = curr->next;
	}
	if (!curr)
		return ;
	if (prev)
		prev->next = curr->next;
	else
		*env = curr->next;
	free(curr->name);
	if (curr->value && *(curr->value))
		free(curr->value);
	free(curr);
}

void	env_lstadd_back(t_env **env, t_env *line)
{
	t_env	*temp;

	if (!line)
		return ;
	if (*env == NULL)
		*env = line;
	else
	{
		temp = env_lstlast(*env);
		temp->next = line;
	}
}
