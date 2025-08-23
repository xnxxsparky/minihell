/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <bcausseq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 23:33:12 by bcausseq          #+#    #+#             */
/*   Updated: 2025/06/01 07:43:28 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	index;

	if (!s || !*s)
		return (NULL);
	index = ft_strlen(s);
	while (index >= 0)
	{
		if (s[index] == (char)c)
			return ((char *)s + index);
		index--;
	}
	return (0);
}
