/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit_while.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <bcausseq@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 00:39:56 by bcausseq          #+#    #+#             */
/*   Updated: 2025/08/11 22:48:04 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit_while(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (1);
	while (ft_isspace(str[i]))
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '+' && str[i] != '-')
			return (1);
		if (str[i - 1] && str[i] && str[i - 1] == str[i]
			&& (str[i] == '+' || str[i] == '-'))
			return (1);
		i++;
	}
	return (0);
}
