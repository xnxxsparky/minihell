/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <bcausseq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:23:48 by bcausseq          #+#    #+#             */
/*   Updated: 2024/10/20 21:31:44 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*src1;
	unsigned char	*src2;

	i = 0;
	if (!s1 || !s2)
		return (0);
	src1 = (unsigned char *)s1;
	src2 = (unsigned char *)s2;
	while (s1[i] && (src1[i] == src2[i]) && (i < n))
		i++;
	if (i >= n)
		return (0);
	return ((int)(src1[i] - src2[i]));
}
