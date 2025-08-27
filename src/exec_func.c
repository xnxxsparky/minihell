/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <bcausseq@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 22:16:58 by bcausseq          #+#    #+#             */
/*   Updated: 2025/08/27 20:01:52 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"
#include "minihell.h"

void	exec(t_shell *shel)
{
	int	count;

	count = 0;
	while (shel->cmd_dec[count].cmd)
		count++;
	reset_sig_child();
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
