/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <bcausseq@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 23:55:38 by bcausseq          #+#    #+#             */
/*   Updated: 2025/09/03 17:55:56 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

static int	parser_redir(t_token *cur)
{
	t_token	*next;

	if (ft_strcmp(cur->token, "<<") != 0 && ft_strcmp(cur->token, ">>")
		!= 0 && ft_strcmp(cur->token, "<") != 0 && ft_strcmp(cur->token,
			">") != 0)
	{
		ft_fprintf(2, "minihell: unexpected token redirection `%s'\n",
			cur->token);
		return (MS_PARSER_ERR);
	}
	next = cur->next;
	if (!next)
	{
		ft_fprintf(2, "minihell: syntax error near unexpected token"
			" `newline'\n");
		return (MS_PARSER_ERR);
	}
	if (next && next->type != MST_WORD && next->type != MST_EXPAND)
	{
		ft_fprintf(2, "minihell: syntax error near unexpected token `%s'\n",
			next->token);
		return (MS_PARSER_ERR);
	}
	return (MS_PARSER_OKK);
}

static int	parser_pipe(t_token *cur, bool *is_fst_cmd)
{
	t_token	*next;

	next = cur->next;
	if ((next && next->type != MST_WORD && next->type != MST_REDIR) || !next)
	{
		if (!next)
			ft_fprintf(2, "minihell: syntax error: unexpected end of file\n");
		else
			ft_fprintf(2, "minihell: syntax error near unexpected token `%s'\n",
				next->token);
		return (MS_PARSER_ERR);
	}
	*is_fst_cmd = true;
	return (MS_PARSER_OKK);
}

static int	parser_frst(t_token *cur, bool *is_fst_cmd)
{
	t_token	*next;

	if (cur->type != MST_WORD && cur->type != MST_REDIR
		&& cur->type != MST_EXPAND)
	{
		ft_fprintf(2, "minihell: syntax error near unexpected token `%s'\n",
			cur->token);
		return (MS_PARSER_ERR);
	}
	if (cur->type == MST_REDIR)
	{
		next = cur->next;
		if (!next || !next->next || next->next->type != MST_WORD)
		{
			ft_fprintf(2, "minihell: syntax error near unexpected token"
				" `newline'\n");
			return (MS_PARSER_ERR);
		}
	}
	*is_fst_cmd = false;
	return (MS_PARSER_OKK);
}

static int	parser(t_shell *shel)
{
	t_token	*cur;
	bool	is_fst_cmd;

	cur = shel->cmd;
	is_fst_cmd = true;
	while (cur)
	{
		if (is_fst_cmd)
		{
			if (parser_frst(cur, &is_fst_cmd))
				return (MS_PARSER_ERR);
		}
		if (cur->type == MST_REDIR)
		{
			if (parser_redir(cur))
				return (MS_PARSER_ERR);
		}
		else if (cur->type == MST_PIPE)
		{
			if (parser_pipe(cur, &is_fst_cmd))
				return (MS_PARSER_ERR);
		}
		cur = cur->next;
	}
	return (MS_PARSER_OKK);
}

int	lexer_handler(t_shell *shel)
{
	fill_token(shel->cmd_user, &(shel->cmd));
	if (!shel->cmd)
		return (MS_PARSER_ERR);
	update_token(shel, &(shel->cmd));
	if (!shel->cmd)
		return (MS_PARSER_ERR);
	quotes_rm(&(shel->cmd));
	if (!shel->cmd)
		return (MS_PARSER_ERR);
	if (parser(shel) != MS_PARSER_OKK)
	{
		free(shel->cmd_user);
		free_tkn(&(shel->cmd));
		shel->retcode = 2;
		return (MS_PARSER_ERR);
	}
	return (MS_PARSER_OKK);
}
