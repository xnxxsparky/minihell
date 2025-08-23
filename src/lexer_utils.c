/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <bcausseq@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 23:50:10 by bcausseq          #+#    #+#             */
/*   Updated: 2025/07/12 02:02:38 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	lexer_get_char(t_lexer *lexer)
{
	if (*lexer->content != '\0')
		return (*lexer->content);
	return (0);
}

void	lexer_advance(t_lexer *lexer, int len)
{
	lexer->content += len;
}

void	skip_spaces(t_lexer *lexer)
{
	while (ft_isspace((char)lexer_get_char(lexer)))
		lexer_advance(lexer, 1);
}

char	lexer_peek(t_lexer *lexer)
{
	if (lexer_get_char(lexer))
		return (lexer->content[1]);
	return (0);
}

void	lexer_token(t_lexer *lexer, int len)
{
	lexer->token.str = lexer->content;
	lexer->token.len = len;
}
