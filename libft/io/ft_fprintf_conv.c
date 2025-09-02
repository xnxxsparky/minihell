/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf_conv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 22:31:47 by bcausseq          #+#    #+#             */
/*   Updated: 2025/09/02 19:03:11 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_fprintf_udig(int fd, int *i, unsigned int disp)
{
	(*i)++;
	return (ft_putunbr_fd((unsigned long long)disp, fd));
}

static int	ft_fprintf_point(int fd, int *i, uintptr_t point)
{
	int	tmp;

	(*i)++;
	if (!point)
		return (ft_putstr_fd("(nil)", fd));
	tmp = write(fd, "0x", 2);
	tmp += ft_putnbr_hex_fd(point, fd, "0123456789abcdef");
	return (tmp);
}

int	ft_fpf_conv_cases(int fd, char const *src, va_list list, int *i)
{
	if (src[1] == 'c')
		return (ft_fprintf_char(fd, i, va_arg(list, int)));
	if (src[1] == '%')
		return (ft_fprintf_perc(fd, i));
	if (src[1] == 'd' || src[1] == 'i')
		return (ft_fprintf_digit(fd, i, va_arg(list, int)));
	if (src[1] == 's')
		return (ft_fprintf_str(fd, i, va_arg(list, char *)));
	if (src[1] == 'X')
		return (ft_fprintf_hex(fd, i, va_arg(list, unsigned int),
				"0123456789ABCDEF"));
	if (src[1] == 'u')
		return (ft_fprintf_udig(fd, i, (unsigned int)va_arg(list, int)));
	if (src[1] == 'p')
		return (ft_fprintf_point(fd, i, va_arg(list, uintptr_t)));
	if (src[1] == 'x')
		return (ft_fprintf_hex(fd, i, va_arg(list, unsigned int),
				"0123456789abcdef"));
	return (-1);
}
