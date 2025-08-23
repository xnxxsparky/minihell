/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <bcausseq@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 01:58:46 by bcausseq          #+#    #+#             */
/*   Updated: 2025/08/23 22:17:12 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"
#include "minihell.h"

void	child_employed(t_shell *shel)
{
	int		in;
	int		out;

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
	fauttoutfree_solo(shel, true, 0, (out < 0 || in < 0));
}

void	exec_solo(t_shell *shel)
{
	int		status;
	pid_t	pid;

	if (apply_builtins(shel, 0) == 1)
	{
		pid = fork();
		if (pid == -1)
			perror("fork");
		if (!pid)
			child_employed(shel);
		else
		{
			while (waitpid(-1, &status, 0) > 0)
			{
				if (WIFEXITED(status))
					shel->retcode = WEXITSTATUS(status);
				else if (WIFSIGNALED(status))
					shel->retcode = 128 + WTERMSIG(status);
			}
			if (shel->cmd_dec[0].fd_in >= 3)
				close(shel->cmd_dec[0].fd_in);
			if (shel->cmd_dec[0].fd_out >= 3)
				close(shel->cmd_dec[0].fd_out);
		}
	}
}

// void	children(t_shell *shel, int pidfd[3], int i, int count)
// {
// 	const t_cmd	curr = shel->cmd_dec[i];
// 	int			in;
// 	int			out;
// 
// 	in = pidfd[0];
// 	out = 0;
// 	if (pidfd[2])
// 		in = pidfd[2];
// 	if (shel->cmd_dec[i].fd_in)
// 		in = shel->cmd_dec[i].fd_in;
// 	if (i != count - 1)
// 		out = pidfd[1];
// 	if (shel->cmd_dec[i].fd_out)
// 		out = shel->cmd_dec[i].fd_out;
// 	if (out >= 3)
// 		dup2(out, STDOUT_FILENO);
// 	if (in >= 3)
// 		dup2(in, STDIN_FILENO);
// 	close_all(curr, pidfd, in, out);
// 	if (!apply_builtins(shel, i))
// 		fauttoutfree_solo(shel, false, i, (in <= 3 || out <= 3));
// 	if (shel->cmd_dec[i].path && in >= 0 && out >= 0)
// 		execve(curr.path, curr.cmd, shel->env_ar);
// 	fauttoutfree_solo(shel, true, i, (in <= 3 || out <= 3));
// }
// 
// void	pipex(t_shell *shel, int pidfd[3], int i, int count)
// {
// 	pid_t	pid;
// 
// 	if (pipe(&pidfd[0]) == -1)
// 		perror("pipe");
// 	pid = fork();
// 	if (pid == -1)
// 		perror("fork");
// 	if (!pid)
// 		children(shel, pidfd, i, count);
// 	if (pidfd[1] > 2)
// 		close(pidfd[1]);
// 	if (pidfd[2] > 2)
// 		close(pidfd[2]);
// 	pidfd[2] = pidfd[0];
// 	return ;
// }

void	children(t_shell *shel, int pipefd[2], int index, int argc)
{
	const t_cmd	curr = shel->cmd_dec[index];
	int			in;
	int			out;

	in = curr.fd_in;
	out = 1;
	if (index + 1 == argc && curr.fd_out)
		out = curr.fd_out;
	else if (index + 1 != argc)
		out = pipefd[WRITE_SIDE];
	dup2(in, STDIN_FILENO);
	if (out != -1)
		dup2(out, STDOUT_FILENO);
	close_all(curr, pipefd, in, out);
	close_all_fds();
	if (!apply_builtins(shel, index))
		fauttoutfree_solo(shel, false, index, (in <= 3 || out <= 3));
	if (shel->cmd_dec[index].path && in >= 0 && out >= 0)
		execve(curr.path, curr.cmd, shel->env_ar);
	fauttoutfree_solo(shel, true, index, (in <= 3 || out <= 3));
}
// 	if (shel->files[0] >= 0)
// 		close(shel->files[0]);
// 	if (shel->files[1] >= 0)
// 		close(shel->files[1]);
// 	if ((ft_strcmp(curr.cmd[0], "NULL") == 0) || in < 0 || out < 0)
// 		fauttoutfree_solo(shel, strerror(2), argc);
// 	if (execve(curr.cmd[0], curr.cmd, curr.env) == -1)
// 		free_all(shel, "Execve Failed...", argc);

void	pipex(t_shell *shel, int pipefd[2], int i, int count)
{
	pid_t	pid;
	bool	need_pipe;

	need_pipe = (i < count - 1);
	if (need_pipe && pipe(pipefd) == -1)
		perror("pipe");
	pid = fork();
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
// 	close(pipefd[READ_SIDE]);

void	exec_plusplus(t_shell *shel, int count)
{
	static int	pidfd[2] = {-1, -1};
	int			i;
	int			status;

	i = -1;
	while (++i < count)
		pipex(shel, pidfd, i, count);
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			shel->retcode = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			shel->retcode = 128 + WTERMSIG(status);
	}
	if (pidfd[READ_SIDE] >= 3)
		close(pidfd[READ_SIDE]);
	close_all_fds();
}
