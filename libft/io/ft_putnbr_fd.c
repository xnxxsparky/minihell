/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <bcausseq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 23:31:09 by bcausseq          #+#    #+#             */
/*   Updated: 2024/10/24 21:52:08 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	int	ret;

	if (fd >= 0)
	{
		ret = 0;
		if (n == -2147483648)
			ret += write(fd, "-2147483648", 11);
		else
		{
			if (n < 0)
			{
				ret += ft_putchar_fd('-', fd);
				n = -n;
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
