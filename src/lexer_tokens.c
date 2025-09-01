/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <bcausseq@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 23:16:04 by bcausseq          #+#    #+#             */
/*   Updated: 2025/09/01 02:18:00 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	lexer_get_var(t_lexer *lexer)
{
	bool	is_first;
	char	c;

	is_first = true;
	lexer_advance(lexer, 1);
	while (1)
	{
		c = lexer_get_char(lexer);
		if (is_first)
		{
			if (!ft_isalpha(c) && c != '_' && c != '?' && c != '|'
				&& c != '<' && c != '>' && c != '$')
				break ;
			is_first = false;
		}
		else
		{
			if (!ft_isalnum(c) && c != '_' && c != '|' && c != '<' && c != '>'
				&& c != '$')
				break ;
		}
		lexer_advance(lexer, 1);
	}
}

void	lexer_get_word(t_lexer *lexer)
{
	char	c;

	while (1)
	{
		c = lexer_get_char(lexer);
		if (c == '\'')
		{
			if (lexer->quote_state == SIMPLE_QUOTES)
				lexer->quote_state = QUOTES_NONE;
			else if (lexer->quote_state == QUOTES_NONE)
				lexer->quote_state = SIMPLE_QUOTES;
		}
		else if (c == '"')
		{
			if (lexer->quote_state == DOUBLE_QUOTES)
				lexer->quote_state = QUOTES_NONE;
			else if (lexer->quote_state == QUOTES_NONE)
				lexer->quote_state = DOUBLE_QUOTES;
		}
		if (cond_break_wd(c, lexer))
			break ;
		lexer_advance(lexer, 1);
	}
}

t_states	next_token(t_lexer *lexer)
{
	char	c;

	skip_spaces(lexer);
	c = lexer_get_char(lexer);
	if (c == '<' || c == '>')
		return (token_redir(lexer));
	else if (c == '|')
		return (token_pipe(lexer));
	else if (c == '$' && lexer->quote_state != SIMPLE_QUOTES)
		return (token_expand(lexer));
	else if (c)
		return (token_word(lexer));
	return (MST_EOF);
}

t_states	lexer_peek_token(t_lexer *lexer)
{
	const char	*save;
	t_states	token;

	save = lexer->content;
	token = next_token(lexer);
	lexer->content = save;
	return (token);
}

bool	token_error(t_lexer lexer, t_states token)
{
	t_states	next;

	if (token == MST_REDIR || token == MST_PIPE)
	{
		next = lexer_peek_token(&lexer);
		if (next != MST_WORD)
		{
			next = next_token(&lexer);
			ft_fprintf(2, "minihell : syntax error near unexpected token "
				"'%.*s'\n", (int)lexer.token.len, lexer.token.str);
			return (true);
		}
	}
	return (false);
}
