/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <bcausseq@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 22:13:04 by bcausseq          #+#    #+#             */
/*   Updated: 2025/08/23 22:13:26 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

void	sig_handle_int_child(int sig)
{
	if (sig == SIGINT)
	{
		g_sig = SIGINT;
		write(1, "\n", 1);
	}
}

void	sig_handle_quit_child(int sig)
{
	if (sig == SIGQUIT)
	{
		g_sig = SIGQUIT;
		write(1, "Quit\n", 5);
	}
}

void	reset_sig_child(void)
{
	struct sigaction	sa;

	sa.sa_handler = sig_handle_int_child;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = sig_handle_quit_child;
	sigaction(SIGQUIT, &sa, NULL);
}
