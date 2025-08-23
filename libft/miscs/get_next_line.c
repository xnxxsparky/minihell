/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:46:02 by bcausseq          #+#    #+#             */
/*   Updated: 2025/08/16 06:45:41 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*read_file(int fd, char *line, char *buff)
{
	int		nb_read;
	char	*temp;

	nb_read = 1;
	while (nb_read > 0)
	{
		nb_read = read(fd, buff, BUFFER_SIZE);
		if (nb_read < 0)
		{
			free(line);
			return (NULL);
		}
		else if (nb_read == 0)
			break ;
		buff[nb_read] = '\0';
		if (!line)
			line = ft_strdup("");
		temp = line;
		line = ft_strjoin(temp, buff, 0, 0);
		free(temp);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	return (line);
}

static char	*stat_cut(char *ret)
{
	int		i;
	char	*line;

	i = 0;
	while (ret[i] != '\n' && ret[i] != '\0')
		i++;
	if (ret[i] == '\0')
		return (NULL);
	line = ft_substr(ret, i + 1, ft_strlen(ret) - i);
	if (!*line)
	{
		free(line);
		return (NULL);
	}
	ret[i + 1] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*ret;
	char		*buff;

	write(1, "minihell_here_docs >", 20);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	ret = read_file(fd, line, buff);
	free(buff);
	if (!ret)
		return (NULL);
	line = stat_cut(ret);
	return (ret);
}
