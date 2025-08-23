/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <bcausseq@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 23:38:31 by bcausseq          #+#    #+#             */
/*   Updated: 2025/06/02 23:48:14 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*ret;
	size_t	i;

	if (!s || !*s)
		return (NULL);
	i = ft_strlen(s);
	if (i > n)
		ret = ft_calloc(n, (sizeof(char) + 1));
	else
		ret = ft_calloc(i, (sizeof(char) + 1));
	if (!ret)
		return (NULL);
	return (ft_strncpy(ret, s, n));
}
