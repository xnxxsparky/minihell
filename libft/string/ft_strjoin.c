/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <bcausseq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 19:19:34 by bcausseq          #+#    #+#             */
/*   Updated: 2025/07/26 21:29:01 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2, bool del_s1, bool del_s2)
{
	char	*ret;

	ret = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), 1);
	if (!ret)
		return (NULL);
	ft_strcat(ret, s1);
	if (del_s1)
		free(s1);
	ft_strcat(ret, s2);
	if (del_s2)
		free(s2);
	return (ret);
}
