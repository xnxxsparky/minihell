/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf_spe_cases_sup.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 06:34:56 by bcausseq          #+#    #+#             */
/*   Updated: 2025/07/28 23:14:50 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_fprintf_perc(int fd, int *i)
{
	(*i)++;
	return (ft_putchar_fd('%', fd));
}

int	ft_fprintf_char(int fd, int *i, char c)
{
	(*i)++;
	return (ft_putchar_fd(c, fd));
}

int	ft_fprintf_digit(int fd, int *i, int disp)
{
	(*i)++;
	return (ft_putnbr_fd(disp, fd));
}

int	ft_fprintf_str(int fd, int *i, char *src)
{
	(*i)++;
	if (!src)
		return (ft_putstr_fd("(null)", fd));
	return (ft_putstr_fd(src, fd));
}

int	ft_fprintf_hex(int fd, int *i, unsigned int disp, char *mode)
{
	(*i)++;
	return (ft_putnbr_hex_fd(disp, fd, mode));
}
