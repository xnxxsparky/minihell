/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <bcausseq@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 19:41:30 by bcausseq          #+#    #+#             */
/*   Updated: 2025/09/05 16:02:40 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

void	redir_in(t_cmd *cmd_final, t_token *cur)
{
	if (cmd_final->fd_in > 2)
		close(cmd_final->fd_in);
	cmd_final->name_fd_in = cur->next->token;
	cmd_final->fd_in = open(cur->next->token, O_RDONLY, 0644);
	if (cmd_final->fd_in == -1)
		ft_fprintf(2, "minihell: %s: %s\n", cur->next->token, strerror(errno));
}

void	redir_out_app(t_cmd *cmd_final, t_token *cur)
{
	if (cmd_final->fd_out > 2)
		close(cmd_final->fd_out);
	cmd_final->name_fd_out = cur->next->token;
	cmd_final->fd_out = open(cur->next->token, O_WRONLY | O_CREAT
			| O_APPEND, 0644);
	if (cmd_final->fd_out == -1)
		ft_fprintf(2, "minihell: %s: %s\n", cur->next->token, strerror(errno));
}

void	redir_out_err(t_cmd *cmd_final, t_token *cur)
{
	if (cmd_final->fd_out > 2)
		close(cmd_final->fd_out);
	cmd_final->name_fd_out = cur->next->token;
	cmd_final->fd_out = open(cur->next->token, O_WRONLY | O_CREAT
			| O_TRUNC, 0644);
	if (cmd_final->fd_out == -1)
		ft_fprintf(2, "minihell: %s: %s\n", cur->next->token, strerror(errno));
}

void	redir_here_doc(t_cmd *cmd_final, t_token **cur, t_shell *shel)
{
	sig_handler_heredoc();
	cmd_final->name_fd_in = ft_random_name(".heredoc", 119);
	if (!cmd_final->name_fd_in)
		return ;
	cmd_final->fd_in = open(cmd_final->name_fd_in,
			O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (cmd_final->fd_in == -1)
		ft_fprintf(2, "This has failed ?\n");
	if (fill_file(&((*cur)->next->token), cmd_final->fd_in, shel) == 1)
	{
		if (errno == EINTR)
		{
			close(cmd_final->fd_in);
			unlink(cmd_final->name_fd_in);
			cmd_final->fd_in = -2;
			return ;
		}
		ft_fprintf(2, "minihell: warning: here-document at line"
			" delimited by end-of-file (wanted `%s')\n", (*cur)->next->token);
	}
	close(cmd_final->fd_in);
	cmd_final->fd_in = open(cmd_final->name_fd_in, O_RDONLY);
	if (cmd_final->fd_in == -1)
		ft_fprintf(2, "How can this fail ?\n");
	unlink(cmd_final->name_fd_in);
}
