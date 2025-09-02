/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_random_name.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <bcausseq@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 21:19:43 by bcausseq          #+#    #+#             */
/*   Updated: 2025/09/02 19:04:55 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_random_name(char *prefix, int size)
{
	static char	name[128] = {0};
	int			fd;
	int			bytes;
	int			i;

	ft_bzero(name, 128);
	fd = open("/dev/random", O_RDONLY);
	if (!prefix || ft_strlen(prefix) + size >= 128)
		return (NULL);
	ft_strcat(name, prefix);
	bytes = read(fd, &name[ft_strlen(prefix)], size);
	close(fd);
	if (bytes != size)
		return (NULL);
	i = ft_strlen(prefix) - 1;
	while (name[++i])
		name[i] = (unsigned char)((((int)name[i] + 256) % 26) + 'a');
	return (name);
}
