/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 02:54:46 by bcausseq          #+#    #+#             */
/*   Updated: 2025/09/02 19:01:42 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_display_fpf(int fd, char const *src, va_list stck)
{
	int	ret;
	int	tmp;
	int	i;

	i = 0;
	ret = 0;
	while (src[i])
	{
		if (src[i] == '%')
		{
			tmp = ft_fpf_conv_cases(fd, src + i, stck, &i);
			if (tmp == -1)
				return (-1);
			ret += tmp;
		}
		else
		{
			write(fd, &src[i], 1);
			ret++;
		}
		i++;
	}
	return (ret);
}

int	ft_fprintf(int fd, char const *src, ...)
{
	va_list	stck;
	int		ret;

	va_start(stck, src);
	ret = ft_display_fpf(fd, src, stck);
	return (ret);
}
