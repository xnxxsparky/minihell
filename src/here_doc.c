/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <bcausseq@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 19:22:17 by bcausseq          #+#    #+#             */
/*   Updated: 2025/09/05 16:00:53 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minihell.h"

static bool	need_quotes_back(char *line)
{
	return (*line == '\'' || *line == '"' || line[ft_strlen(line) - 1] == '\''
		|| line[ft_strlen(line) - 1] == '"');
}

static void	lim_handler(char **delim, char **lim, bool *xpd)
{
	t_token	*cmd;

	if (need_quotes_back(*delim))
	{
		cmd = cmd_init(delim);
		if (!cmd)
			return ;
		quotes_rm(&cmd);
		if (!cmd)
			return ;
		free(cmd->token);
		free(*delim);
		(*delim) = ft_strdup(*lim);
		*xpd = false;
	}
	else
	{
		*lim = ft_strdup(*delim);
		if (!(*lim))
			return ;
		*xpd = true;
	}
}

static char	*get_new(char *line, int len, char *c, char *d)
{
	char	*new;

	if (*line == '\'' || *line == '"')
		*c = *line;
	if (line[len - 1] == '\'' || line[len - 1] == '"')
		*d = line[len - 1];
	if (*c)
		len--;
	if (*d)
		len--;
	if (*c)
		new = ft_strndup(&line[1], len);
	else
		new = ft_strndup(line, len);
	if (!new)
		return (NULL);
	return (new);
}

static void	wrt_in_fd(bool xpd, char *line, int fd, t_shell *shel)
{
	char	*new;
	int		len;
	char	c;
	char	d;

	c = '\0';
	d = '\0';
	len = ft_strlen(line);
	if (!xpd)
		write(fd, line, ft_strlen(line));
	else
	{
		new = get_new(line, len, &c, &d);
		if (!new)
			return ;
		replace(shel, new, &new);
		if (!new)
			return ;
		wrt(c, d, new, fd);
		free(new);
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
		line = readline("minihell_here_docs >");
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
