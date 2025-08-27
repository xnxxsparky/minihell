/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <bcausseq@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 00:05:05 by bcausseq          #+#    #+#             */
/*   Updated: 2025/08/27 22:17:37 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

int	apply_builtins_forked(t_shell *shel, int index)
{
	static t_op	funcs[8] = {
	{"exit", ft_exit}, {"pwd", ft_pwd},
	{"export", ft_export}, {"unset", ft_unset},
	{"env", ft_env}, {"cd", ft_cd}, {"echo", ft_echo},
	{0},
	};
	int			i;

	i = -1;
	while (funcs[++i].name)
	{
		if (ft_strcmp(shel->cmd_dec[index].cmd[0], funcs[i].name) == 0)
		{
			funcs[i].func(shel, index);
			return (0);
		}
	}
	return (1);
}

void	handle_dup(int arr[2], bool std_dup)
{
	if (!arr[0] && !arr[1])
	{
		arr[0] = dup(STDIN_FILENO);
		arr[1] = dup(STDOUT_FILENO);
		signal(SIGPIPE, SIG_IGN);
	}
	if (std_dup)
	{
		dup2(arr[0], STDIN_FILENO);
		dup2(arr[1], STDOUT_FILENO);
		close(arr[0]);
		close(arr[1]);
		signal(SIGPIPE, SIG_DFL);
	}
	return ;
}

void	handle_pipe(t_shell *shel, int *in, int *out)
{
	(*in) = 0;
	(*out) = 1;
	if (shel->cmd_dec[0].fd_in)
		(*in) = shel->cmd_dec[0].fd_in;
	if (shel->cmd_dec[0].fd_out)
		(*out) = shel->cmd_dec[0].fd_out;
	if ((*in) >= 3)
	{
		dup2((*in), STDIN_FILENO);
		close(shel->cmd_dec[0].fd_in);
		close((*in));
	}
	if ((*out) >= 3)
	{
		dup2((*out), STDOUT_FILENO);
		close(shel->cmd_dec[0].fd_out);
		close((*out));
	}
}
