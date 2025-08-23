/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypoulett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 02:25:18 by ypoulett          #+#    #+#             */
/*   Updated: 2025/08/23 17:57:16 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

void	ft_unset(t_shell *shel, int index)
{
	t_env	*target;

	target = env_finder(shel->env, shel->cmd_dec[index].cmd[1]);
	if (target)
	{
		env_lstdelone(&(shel->env), target);
		env_join(&(shel->env_ar), shel->env);
		if (!shel->env_ar)
			return ;
	}
	shel->retcode = 0;
}
