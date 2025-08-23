/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_add_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 22:30:16 by bcausseq          #+#    #+#             */
/*   Updated: 2025/07/28 23:15:16 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_hex_fd(unsigned long n, int fd, char *mode)
{
	int	ret;

	if (fd >= 0)
	{
		ret = 0;
		if (n > 15)
		{
			ret += ft_putnbr_hex_fd(n / 16, fd, mode);
			ret += ft_putchar_fd(mode[n % 16], fd);
		}
		else
			ret += ft_putchar_fd(mode[n % 16], fd);
		return (ret);
	}
	return (-1);
}

int	ft_putunbr_fd(long long n, int fd)
{
	int	ret;

	if (fd >= 0)
	{
		ret = 0;
		if (n == -4294967295)
			ret += write(fd, "-4294967295", 11);
		else
		{
			if (n < 0)
			{
				n += 4294967295 + 1;
			}
			if (n > 9)
			{
				ret += ft_putnbr_fd(n / 10, fd);
				ret += ft_putchar_fd(n % 10 + '0', fd);
			}
			else
				ret += ft_putchar_fd(n % 10 + '0', fd);
		}
		return (ret);
	}
	return (-1);
}
