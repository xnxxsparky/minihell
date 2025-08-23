/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypoulett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 01:59:51 by ypoulett          #+#    #+#             */
/*   Updated: 2025/08/23 17:57:16 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

t_env	*env_finder(t_env *env, char *name)
{
	t_env	*curr;

	curr = env;
	while (curr && ft_strcmp(curr->name, name) != 0)
	{
		curr = curr->next;
	}
	if (!curr)
		return (NULL);
	else
		return (curr);
}

void	splitter(t_env **newenv, char *eq, char **env, int i)
{
	t_env	*node;
	char	*val;
	char	*name;

	name = ft_strndup(env[i], eq - env[i]);
	if (!name)
		return ;
	if (!ft_strcmp(name, "SHLVL"))
		val = ft_itoa((int)ft_atoll(eq + 1) + 1);
	else
		val = ft_strdup(eq + 1);
	if (!val)
		return (free(name));
	node = env_lstnew(name, val);
	free(name);
	free(val);
	if (!node)
		return ;
	env_lstadd_back(newenv, node);
}

t_env	*env_instantiate(char **env)
{
	t_env	*newenv;
	char	*eq;
	int		i;

	newenv = NULL;
	ft_bzero(newenv, sizeof(t_env));
	i = 0;
	if (!env)
		return (newenv);
	while (env[i])
	{
		eq = ft_strchr(env[i], '=');
		if (eq)
			splitter(&(newenv), eq, env, i);
		i++;
	}
	return (newenv);
}
