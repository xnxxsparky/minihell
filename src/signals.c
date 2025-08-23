/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypoulett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 01:34:16 by ypoulett          #+#    #+#             */
/*   Updated: 2025/08/13 15:42:32 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

volatile sig_atomic_t	g_sig = 0;

void	sig_handle_int(int sig)
{
	if (sig == SIGINT)
	{
		g_sig = SIGINT;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sig_handler_classic(void)
{
	struct sigaction	sa;

	sa.sa_handler = sig_handle_int;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

void	reset_state(void)
{
	g_sig = 0;
	sig_handler_classic();
}

void	handle_input(t_shell *shel)
{
	(void)shel;
	if (g_sig == SIGINT)
	{
		shel->retcode = 128 + SIGINT;
		g_sig = 0;
	}
}

// void	sigint_func(int sig)
// {
// 	(void)sig;
// 	write(1, "\n", 1);
// 	rl_replace_line("", 0);
// 	rl_on_new_line();
// 	g_sig = 130;
// 	rl_redisplay();
// }
// 
// void	sigabrt_func(int sig)
// {
// 	(void)sig;
// 	g_sig = SIGABRT;
// 	write(1, "abort\n", 6);
// }
// 
// void	sigsegv_func(int sig)
// {
// 	(void)sig;
// 	g_sig = 139;
// 	write(2, "Segmentation fault\n", 19);
// 	exit(11);
// }
