/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errs_ret_code.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <bcausseq@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 18:42:09 by bcausseq          #+#    #+#             */
/*   Updated: 2025/09/03 18:42:40 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

void	ret_code_errs_handle(t_shell *shel)
{
	if (errno == EACCES)
		shel->retcode = 1;
	else
		shel->retcode = 130;
}

bool	fail_open(t_cmd *cmd_final)
{
	if (cmd_final->fd_in == -1 || cmd_final->fd_out == -1)
	{
		errno = EACCES;
		return (true);
	}
	return (false);
}
