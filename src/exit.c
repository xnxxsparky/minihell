/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <bcausseq@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 04:31:17 by bcausseq          #+#    #+#             */
/*   Updated: 2025/08/16 04:59:33 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

void	free_cmd_dec(t_cmd **cmd_dec)
{
	int	i;

	i = 0;
	while ((*cmd_dec)[i].cmd)
	{
		free((*cmd_dec)[i].path);
		free((*cmd_dec)[i].cmd);
		i++;
	}
	free(*cmd_dec);
}

void	full_free(t_shell *shel, bool *ret_need, int *ret, int index)
{
	if (shel->cmd_dec[index].cmd[1]
		&& ft_isdigit_while(shel->cmd_dec[index].cmd[1]))
	{
		ft_fprintf(2, "minihell: exit: %s: numeric argument required\n",
			shel->cmd_dec[index].cmd[1]);
		(*ret_need) = true;
		(*ret) = 2;
	}
	free_free(shel);
}

void	ft_exit(t_shell *shel, int index)
{
	int		ret;
	bool	ret_need;

	ret_need = false;
	if (!ft_isdigit_while(shel->cmd_dec[index].cmd[1])
		&& shel->cmd_dec[index].cmd[2])
	{
		ft_fprintf(2, "minihell: exit: too many arguments\n");
		shel->retcode = 1;
		return ;
	}
	else if (shel->cmd_dec[index].cmd[1])
	{
		ret = ft_atoll(shel->cmd_dec[index].cmd[1]);
		ret_need = true;
	}
	full_free(shel, &ret_need, &ret, index);
	if (ret_need)
		exit(ret);
	exit(shel->retcode);
}
