/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_signals_and_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <bcausseq@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 22:13:04 by bcausseq          #+#    #+#             */
/*   Updated: 2025/09/03 20:30:15 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

void	reset_sig_child(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	waiting_plusplus(t_shell *shel, int j, int pidfd[2])
{
	int	status;

	while (waitpid(shel->pids[j], &status, 0) > 0)
	{
		if (WIFEXITED(status))
			shel->retcode = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == 3)
				ft_fprintf(1, "Quit\n");
			else if (WTERMSIG(status) == 2)
				ft_fprintf(1, "\n");
			shel->retcode = 128 + WTERMSIG(status);
		}
		display_errs(shel, j, shel->retcode);
	}
	if (pidfd[READ_SIDE] >= 3)
		close(pidfd[READ_SIDE]);
	close_all_fds();
	return ;
}

void	waiting_solo(t_shell *shel)
{
	int	status;

	while (waitpid(shel->pids[0], &status, 0) > 0)
	{
		if (WIFEXITED(status))
			shel->retcode = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == 3)
				ft_fprintf(1, "Quit\n");
			else if (WTERMSIG(status) == 2)
				ft_fprintf(1, "\n");
			shel->retcode = 128 + WTERMSIG(status);
		}
		display_errs(shel, 0, shel->retcode);
	}
	close_in_out_solo(shel);
	return ;
}

void	setup_child(void)
{
	reset_sig_child();
	rl_clear_history();
}
