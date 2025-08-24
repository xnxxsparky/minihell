/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <bcausseq@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 02:59:54 by bcausseq          #+#    #+#             */
/*   Updated: 2025/08/24 19:43:14 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

static bool	return_line_question_mark(char *wr)
{
	if (!wr || *wr != '-' || (*wr && !*(wr + 1)))
		return (true);
	wr++;
	while (*wr == 'n')
		wr++;
	if (*wr)
		return (true);
	return (false);
}

static bool	need_space(char *cmp)
{
	if (cmp && ft_strcmp(cmp, "$"))
		return (true);
	return (false);
}

void	ft_echo(t_shell *shel, int index)
{
	char	*wr;
	bool	n;
	int		i;

	i = 1;
	wr = shel->cmd_dec[index].cmd[i];
	n = true;
	while (return_line_question_mark(wr) == false)
	{
		n = false;
		i++;
		if (shel->cmd_dec[index].cmd[i])
			wr = shel->cmd_dec[index].cmd[i];
	}
	while (wr)
	{
		write(1, wr, ft_strlen(wr));
		i++;
		if (need_space(shel->cmd_dec[index].cmd[i]))
			write(1, " ", 1);
		wr = shel->cmd_dec[index].cmd[i];
	}
	if (n == true)
		write(1, "\n", 1);
	shel->retcode = 0;
}
