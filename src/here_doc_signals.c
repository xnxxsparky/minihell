/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_signals.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <bcausseq@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 22:09:31 by bcausseq          #+#    #+#             */
/*   Updated: 2025/09/05 09:11:15 by bcausseq         ###   ########.fr       */
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
	write(fd, line, ft_strlen(line) - 1);
	if (d)
		write(fd, &d, 1);
	write(fd, "\n", 1);
}
