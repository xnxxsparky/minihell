/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <bcausseq@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 02:11:49 by bcausseq          #+#    #+#             */
/*   Updated: 2025/08/14 18:49:09 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

void	ft_pwd(t_shell *shel, int index)
{
	char	buf[4096];

	ft_bzero(buf, 4096);
	(void)index;
	(void)shel;
	ft_fprintf(1, "%s\n", getcwd(buf, 4096));
	shel->retcode = 0;
}
