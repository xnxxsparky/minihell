/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <bcausseq@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 23:51:49 by bcausseq          #+#    #+#             */
/*   Updated: 2025/08/23 22:10:59 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_states	token_redir(t_lexer *lexer)
{
	int		len;
	char	next;

	len = 1;
	next = lexer_peek(lexer);
	if (next == '<' || next == '>')
		len++;
	lexer_token(lexer, len);
	lexer_advance(lexer, len);
	return (MST_REDIR);
}

t_states	token_pipe(t_lexer *lexer)
{
	lexer_token(lexer, 1);
	lexer_advance(lexer, 1);
	return (MST_PIPE);
}

t_states	token_expand(t_lexer *lexer)
{
	const char	*save = lexer->content;
	int			len;

	lexer_get_var(lexer);
	len = lexer->content - save;
	lexer->content = save;
	lexer_token(lexer, len);
	lexer_advance(lexer, len);
	return (MST_EXPAND);
}

t_states	token_word(t_lexer *lexer)
{
	const char	*save = lexer->content;
	int			len;

	lexer_get_word(lexer);
	len = lexer->content - save;
	lexer->content = save;
	lexer_token(lexer, len);
	lexer_advance(lexer, len);
	return (MST_WORD);
}

bool	cond_break_wd(char c, t_lexer *lexer)
{
	if ((lexer->quote_state == QUOTES_NONE && ft_isspace(c)) || c == '\0'
		|| (c == '|' && lexer->quote_state == QUOTES_NONE) || (c == '<'
			&& lexer->quote_state == QUOTES_NONE)
		|| (c == '>' && lexer->quote_state == QUOTES_NONE))
		return (true);
	return (false);
}
