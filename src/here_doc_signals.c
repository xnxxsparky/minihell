/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_signals.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <bcausseq@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 22:09:31 by bcausseq          #+#    #+#             */
/*   Updated: 2025/09/05 16:00:53 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

static void	sig_handle_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_sig = SIGINT;
		write(1, "\n", 1);
	}
}

void	sig_handler_heredoc(void)
{
	struct sigaction	sa;

	sa.sa_handler = sig_handle_heredoc;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

void	wrt(char c, char d, char *line, int fd)
{
	if (c)
		write(fd, &c, 1);
	write(fd, line, ft_strlen(line));
	if (d)
		write(fd, &d, 1);
	write(fd, "\n", 1);
}

t_token	*cmd_init(char **delim)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	new->token = ft_strdup(*delim);
	if (!new->token)
		return (NULL);
	new->type = MST_WORD;
	new->expanded = 0;
	new->next = NULL;
	return (new);
}
