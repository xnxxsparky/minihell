/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypoulett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 02:07:46 by ypoulett          #+#    #+#             */
/*   Updated: 2025/09/02 02:04:06 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

void	add_to_env(t_shell *shel, char *arg, char *eq)
{
	char	*name;
	char	*val;

	name = ft_strndup(arg, eq - arg);
	if (!name)
		return ;
	if (eq)
		val = ft_strdup(eq + 1);
	else
		val = NULL;
	if (!val)
	{
		xprt_edit(&(shel->env), name, NULL);
		free(name);
		free(arg);
		return ;
	}
	xprt_edit(&(shel->env), name, val);
	free(name);
	free(val);
	free(arg);
}

void	export_export(t_shell *shel, int index)
{
	t_env	*cur;

	if (!shel->cmd_dec[index].cmd[1])
	{
		cur = shel->env;
		while (cur)
		{
			if (!cur->value)
				ft_fprintf(1, "declare -x %s=\"\"\n", cur->name);
			else
				ft_fprintf(1, "declare -x %s=\"%s\"\n", cur->name, cur->value);
			cur = cur->next;
		}
	}
}

void	xprt_nrm(t_shell *shel, int index, int i)
{
	char	*arg;
	char	*eq;

	arg = ft_strdup(shel->cmd_dec[index].cmd[i]);
	eq = ft_strchr(arg, '=');
	if (arg)
		add_to_env(shel, arg, eq);
}

void	ft_export(t_shell *shel, int index)
{
	int		i;

	i = 1;
	if (!shel->cmd_dec[index].cmd[1])
		return (export_export(shel, index));
	while (shel->cmd_dec[index].cmd[i])
	{
		if (!valid_xprt_name(shel->cmd_dec[index].cmd[i]))
		{
			ft_fprintf(2, "minihell: export: `%s': not a valid identifier\n",
				shel->cmd_dec[index].cmd[i]);
			shel->retcode = 1;
			return ;
		}
		i++;
	}
	i = 1;
	while (shel->cmd_dec[index].cmd[i])
	{
		xprt_nrm(shel, index, i);
		i++;
	}
	env_join(&(shel->env_ar), shel->env);
	shel->retcode = 0;
}
