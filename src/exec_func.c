/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <bcausseq@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 22:16:58 by bcausseq          #+#    #+#             */
/*   Updated: 2025/09/02 00:09:51 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

void	exec(t_shell *shel)
{
	int	count;

	count = 0;
	while (shel->cmd_dec[count].cmd)
		count++;
	hist_adder(shel->cmd_dec, count, shel->cmd_user);
	shel->pids = ft_calloc(count, sizeof(int));
	if (!shel->pids)
		return ;
	if (count == 1)
		exec_solo(shel);
	else if (count > 1)
		exec_plusplus(shel, count);
	free(shel->pids);
	return ;
}

void	close_in_out_solo(t_shell *shel)
{
	if (shel->cmd_dec[0].fd_in >= 3)
		close(shel->cmd_dec[0].fd_in);
	if (shel->cmd_dec[0].fd_out >= 3)
		close(shel->cmd_dec[0].fd_out);
}

void	display_errs(t_shell *shel, int index, int status)
{
	if (status == 127)
	{
		if (!ft_strncmp(shel->cmd_dec[index].cmd[0], "./", 2)
			&& access(shel->cmd_dec[index].cmd[0], F_OK) != 0)
			ft_fprintf(2, "minihell: %s: No such file or directory\n",
				shel->cmd_dec[index].cmd[0]);
		else
			ft_fprintf(2, "%s: command not found\n",
				shel->cmd_dec[index].cmd[0]);
	}
	else if (status == 126)
		ft_fprintf(2, "minihell: %s: Permission denied\n",
			shel->cmd_dec[index].cmd[0]);
	return ;
}
