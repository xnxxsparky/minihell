/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <bcausseq@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 19:22:17 by bcausseq          #+#    #+#             */
/*   Updated: 2025/08/23 22:09:52 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

bool	need_quotes_back(char *line)
{
	return (*line == '\'' || *line == '"' || line[ft_strlen(line) - 1] == '\''
		|| line[ft_strlen(line) - 1] == '"');
}

void	lim_handler(char **delim, char **lim, bool *xpd)
{
	t_token	*cmd;

	if (need_quotes_back(*delim))
	{
		cmd = &(t_token){.token = ft_strdup(*delim), .type = MST_WORD,
			.expanded = 0, .next = NULL};
		quotes_rm(&cmd);
		if (!cmd)
			return ;
		*lim = ft_strjoin(cmd->token, "\n", false, false);
		if (!(*lim))
			return ;
		free(cmd->token);
		free(*delim);
		(*delim) = ft_strdup(*lim);
		*xpd = false;
	}
	else
	{
		*lim = ft_strjoin(*delim, "\n", false, false);
		if (!(*lim))
			return ;
		*xpd = true;
	}
}

void	wrt_in_fd(bool xpd, char *line, int fd, t_shell *shel)
{
	t_token	*cmd;
	char	c;

	c = '\0';
	if (!xpd)
		write(fd, line, ft_strlen(line));
	else
	{
		if (*line == '\'' || *line == '"')
		{
			c = *line;
			cmd = &(t_token){.token = line, .type = MST_WORD,
				.expanded = 0, .next = NULL};
			quotes_rm(&cmd);
			line = cmd->token;
		}
		replace(shel, line, &line);
		if (c)
			write(fd, &c, 1);
		write(fd, line, ft_strlen(line) - 1);
		if (c)
			write(fd, &c, 1);
		write(fd, "\n", 1);
	}
	free(line);
}

int	fill_file(char **delim, int fd, t_shell *shel)
{
	char	*lim;
	char	*line;
	int		err;
	bool	xpd;

	lim_handler(delim, &lim, &xpd);
	err = lim == NULL;
	if (!lim)
		return (err);
	while (lim && !err)
	{
		line = get_next_line(0);
		err = err || line == NULL;
		if (!line)
			break ;
		if (!ft_strcmp(lim, line))
		{
			free(line);
			break ;
		}
		wrt_in_fd(xpd, line, fd, shel);
	}
	free(lim);
	return (err);
}
