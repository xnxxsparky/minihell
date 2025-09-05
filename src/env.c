/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <bcausseq@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 05:31:35 by bcausseq          #+#    #+#             */
/*   Updated: 2025/08/12 02:41:39 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

void	ft_env(t_shell *shel, int index)
{
	t_env	*tmp;
	int		i;
	int		len;

	if (shel->cmd_dec[index].cmd[1])
	{
		shel->retcode = 127;
		return ;
	}
	len = env_len(shel->env);
	i = -1;
	tmp = shel->env;
	while (++i <= len)
	{
		if (tmp->value)
			ft_fprintf(1, "%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
	shel->retcode = 0;
}
