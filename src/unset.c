/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypoulett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 02:25:18 by ypoulett          #+#    #+#             */
/*   Updated: 2025/09/04 21:59:30 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

void	ft_unset(t_shell *shel, int index)
{
	t_env	*target;
	char	*to_del;
	int		i;

	i = 1;
	to_del = shel->cmd_dec[index].cmd[i];
	while (to_del)
	{
		target = env_finder(shel->env, to_del);
		if (target)
		{
			env_lstdelone(&(shel->env), target);
			env_join(&(shel->env_ar), shel->env);
			if (!shel->env_ar)
				return ;
		}
		shel->retcode = 0;
		i++;
		to_del = shel->cmd_dec[index].cmd[i];
	}
}
