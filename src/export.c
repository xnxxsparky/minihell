/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypoulett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 02:07:46 by ypoulett          #+#    #+#             */
/*   Updated: 2025/09/05 01:21:25 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

static void	add_to_env(t_shell *shel, char *arg, char *eq)
{
	char	*name;
	char	*val;

	name = ft_strndup(arg, eq - arg);
	if (!name)
		return ;
	if (eq)
	{
		if (eq[0] == '=')
			val = ft_calloc(1, 1);
		else
			val = ft_strdup(eq + 1);
	}
	else
		val = NULL;
	if (!val)
	{
		xprt_edit(&(shel->env), name, NULL, eq);
		free_args(name, arg, NULL, NULL);
		return ;
	}
	xprt_edit(&(shel->env), name, val, eq);
	free_args(name, arg, val, NULL);
}

static void	export_export(t_shell *shel, int index)
{
	t_env	*cur;

	if (!shel->cmd_dec[index].cmd[1])
	{
		cur = shel->env;
		while (cur)
		{
			if (!cur->value)
				ft_fprintf(1, "declare -x %s\n", cur->name);
			else
				ft_fprintf(1, "declare -x %s=\"%s\"\n", cur->name, cur->value);
			cur = cur->next;
		}
	}
}

static void	xprt_nrm(t_shell *shel, int index, int i)
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
	bool	errs;

	i = 0;
	errs = false;
	if (!shel->cmd_dec[index].cmd[1])
		return (export_export(shel, index));
	while (shel->cmd_dec[index].cmd[++i])
	{
		if (!valid_xprt_name(shel->cmd_dec[index].cmd[i]))
		{
			ft_fprintf(2, "minihell: export: `%s': not a valid identifier\n",
				shel->cmd_dec[index].cmd[i]);
			shel->retcode = 1;
			errs = true;
			break ;
		}
		xprt_nrm(shel, index, i);
	}
	env_join(&(shel->env_ar), shel->env);
	if (!shel->env_ar)
		return ;
	if (!errs)
		shel->retcode = 0;
}
