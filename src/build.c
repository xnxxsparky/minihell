/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <bcausseq@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 22:11:59 by bcausseq          #+#    #+#             */
/*   Updated: 2025/09/02 19:09:11 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

static t_token	*redirection_handler(t_cmd *cmd_final, t_token **cur, t_shell *shel)
{
	if (!ft_strncmp((*cur)->token, "<", 1))
	{
		if (!ft_strncmp((*cur)->token, "<<", 2))
		{
			if (cmd_final->fd_in)
				close(cmd_final->fd_in);
			redir_here_doc(cmd_final, cur, shel);
			reset_state();
			if (cmd_final->fd_in <= -2)
				return (NULL);
		}
		else
			redir_in(cmd_final, (*cur));
	}
	else
	{
		if (!ft_strncmp((*cur)->token, ">>", 2))
			redir_out_app(cmd_final, (*cur));
		else
			redir_out_err(cmd_final, (*cur));
	}
	return ((*cur)->next);
}

static void	append(t_cmd *cmd_final, t_token *cmd, t_shell *shel)
{
	int	i;

	i = 0;
	if (!cmd_final->cmd[i])
	{
		cmd_final->cmd[i] = cmd->token;
		parse(shel, cmd->token, &(cmd_final->path));
		if (!cmd_final->path)
			return ;
		return ;
	}
	while (cmd_final->cmd[i])
		i++;
	cmd_final->cmd[i] = cmd->token;
}

static void	cmd_alloc_while(t_token *cur, t_cmd *final, int *i, int *count)
{
	if (cur->type == MST_WORD || cur->type == MST_REDIR)
		(*count)++;
	else if (cur->type == MST_PIPE)
	{
		final[(*i)].cmd = ft_calloc((*count) + 2, sizeof(char *));
		if (!final[(*i)].cmd)
			return ;
		(*count) = 0;
		(*i)++;
	}
}

void	cmd_alloc(t_cmd **cmd_final, t_token *cmd)
{
	t_cmd	*final;
	t_token	*cur;
	int		len_cmd;
	int		i;
	int		count;

	i = 0;
	cur = cmd;
	len_cmd = cmd_len_calc(cmd);
	count = 0;
	final = ft_calloc(len_cmd + 1, sizeof(*final));
	if (!cmd_final)
		return ;
	while (cur)
	{
		cmd_alloc_while(cur, final, &i, &count);
		if (cur->type == MST_PIPE && ! !final[i].cmd)
			return ;
		cur = cur->next;
	}
	final[i].cmd = ft_calloc(count + 2, sizeof(char *));
	if (!final[i].cmd)
		return ;
	*cmd_final = final;
}

void	buid_t_cmd(t_shell *shel, t_cmd **cmd_dec)
{
	t_cmd	*cmd_final;
	t_token	*cur;
	int		i;

	*cmd_dec = NULL;
	i = 0;
	cur = shel->cmd;
	cmd_alloc(&cmd_final, shel->cmd);
	if (!cmd_final)
		return ;
	while (cur)
	{
		if (cur->type == MST_REDIR)
		{
			cur = redirection_handler(&cmd_final[i], &cur, shel);
			if (!cur)
				return (free_cmd_dec(&cmd_final));
		}
		else if (cur->type == MST_PIPE)
			i++;
		else
			append(&cmd_final[i], cur, shel);
		cur = cur->next;
	}
	*cmd_dec = cmd_final;
}
