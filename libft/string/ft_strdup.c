/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <bcausseq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 23:45:59 by bcausseq          #+#    #+#             */
/*   Updated: 2025/09/02 18:35:39 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*ret;

	if (!s || !*s)
		return (NULL);
	i = ft_strlen(s);
	ret = (char *)ft_calloc(i, sizeof(char) + 1);
	if (!ret)
		return (NULL);
	return (ft_strcpy(ret, s));
}
