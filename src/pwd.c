/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <bcausseq@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 02:11:49 by bcausseq          #+#    #+#             */
/*   Updated: 2025/09/05 00:43:24 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"
#include "minihell.h"
#include <unistd.h>

void	ft_pwd(t_shell *shel, int index)
{
	char	buf[4096];

	ft_bzero(buf, 4096);
	(void)index;
	(void)shel;
	if (getcwd(buf, 4096) != NULL)
		ft_fprintf(1, "%s\n", buf);
	else
		ft_fprintf(1, "getcwd: cannot access parent directories: No such file"
			" or directory\n");
	shel->retcode = 0;
}
