/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <bcausseq@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 22:16:58 by bcausseq          #+#    #+#             */
/*   Updated: 2025/08/23 22:17:09 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

void	exec(t_shell *shel)
{
	int	count;

	count = 0;
	while (shel->cmd_dec[count].cmd)
		count++;
	reset_sig_child();
	hist_adder(shel->cmd_dec, count, shel->cmd_user);
	if (count == 1)
		exec_solo(shel);
	else if (count > 1)
		exec_plusplus(shel, count);
	return ;
}
