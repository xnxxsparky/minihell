/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <bcausseq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:35:15 by bcausseq          #+#    #+#             */
/*   Updated: 2025/08/28 19:02:51 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "libft.h"

// static bool	check_overflow(int digit, long long ret)
// {
// 	if (ret > (LLONG_MAX - digit) / 10)
// 		return (true);
// 	if (ret > (LLONG_MIN - digit) / 10)
// 		return (true);
// 	return (false);
// }

long long	ft_atoll(const char *nptr)
{
	long long	ret;
	int			i;
	int			sign;

	ret = 0;
	i = 0;
	sign = 1;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= (-1);
		i++;
	}
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
	{
		if ((ret * 10 + (nptr[i] - '0')) < ret)
		{
			errno = ERANGE;
			return (0);
		}
		ret = ret * 10 + (nptr[i++] - '0');
	}
	return (sign * ret);
}
