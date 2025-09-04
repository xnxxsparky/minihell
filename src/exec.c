/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <bcausseq@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 01:58:46 by bcausseq          #+#    #+#             */
/*   Updated: 2025/09/05 01:05:15 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

static void	child_employed(t_shell *shel)
{
	int		in;
	int		out;

	setup_child();
	in = 0;
	out = 0;
	if (shel->cmd_dec[0].fd_in)
		in = shel->cmd_dec[0].fd_in;
	if (shel->cmd_dec[0].fd_out)
		out = shel->cmd_dec[0].fd_out;
	if (in >= 3)
	{
		dup2(in, STDIN_FILENO);
		close(shel->cmd_dec[0].fd_in);
		close(in);
	}
	if (out >= 3)
	{
		dup2(out, STDOUT_FILENO);
		close(shel->cmd_dec[0].fd_out);
		close(out);
	}
	if (shel->cmd_dec[0].path && out >= 0 && in >= 0)
		execve(shel->cmd_dec[0].path, shel->cmd_dec->cmd, shel->env_ar);
	full_free(shel, true, 0);
}

void	exec_solo(t_shell *shel)
{
	pid_t	pid;

	if (apply_builtins(shel, 0) == 1)
	{
		signal(SIGINT, SIG_IGN);
		pid = fork();
		shel->pids[0] = pid;
		if (pid == -1)
			perror("fork");
		if (!pid)
			child_employed(shel);
		else
		{
			waiting_solo(shel);
		}
	}
}

static void	children(t_shell *shel, int pipefd[2], int index, int argc)
{
	const t_cmd	curr = shel->cmd_dec[index];
	int			in;
	int			out;

	setup_child();
	in = curr.fd_in;
	out = 1;
	if ((index + 1 == argc && curr.fd_out) || curr.fd_out)
		out = curr.fd_out;
	else if (index + 1 != argc)
		out = pipefd[WRITE_SIDE];
	dup2(in, STDIN_FILENO);
	if (out != -1)
		dup2(out, STDOUT_FILENO);
	close_all(curr, pipefd, in, out);
	close_all_fds();
	if (!apply_builtins_forked(shel, index))
		full_free(shel, false, index);
	if (shel->cmd_dec[index].path && in >= 0 && out >= 0)
		execve(curr.path, curr.cmd, shel->env_ar);
	full_free(shel, true, index);
}

static void	pipex(t_shell *shel, int pipefd[2], int i, int count)
{
	pid_t	pid;
	bool	need_pipe;

	need_pipe = (i < count - 1);
	if (need_pipe && pipe(pipefd) == -1)
		perror("pipe");
	pid = fork();
	shel->pids[i] = pid;
	if (pid == -1)
		perror("fork");
	if (!pid)
		children(shel, pipefd, i, count);
	if (need_pipe && pipefd[WRITE_SIDE] >= 0)
		close(pipefd[WRITE_SIDE]);
	if (shel->cmd_dec[i].fd_in > 2)
		close(shel->cmd_dec[i].fd_in);
	if (need_pipe)
	{
		if (!(shel->cmd_dec[i + 1].fd_in))
			shel->cmd_dec[i + 1].fd_in = pipefd[READ_SIDE];
		else if (pipefd[READ_SIDE] > 2)
			close(pipefd[READ_SIDE]);
	}
}

void	exec_plusplus(t_shell *shel, int count)
{
	static int	pidfd[2] = {-1, -1};
	int			i;
	int			j;

	signal(SIGINT, SIG_IGN);
	i = -1;
	while (++i < count)
		pipex(shel, pidfd, i, count);
	j = -1;
	while (++j < count)
	{
		waiting_plusplus(shel, j, pidfd);
	}
}
