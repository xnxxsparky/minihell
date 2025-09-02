/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <bcausseq@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:02:48 by bcausseq          #+#    #+#             */
/*   Updated: 2025/09/02 19:42:50 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	free_tkn(t_token **cmd)
{
	t_token	*cur;

	if (!cmd || !*cmd)
		return ;
	while (*cmd)
	{
		cur = *cmd;
		free(cur->token);
		(*cmd) = (*cmd)->next;
		free(cur);
	}
}

static t_token	*tkn_last(t_token *head)
{
	t_token	*cur;

	cur = head;
	while (cur->next)
		cur = cur->next;
	return (cur);
}

static void	tkn_addback(t_token **head, t_token *new)
{
	t_token	*tmp;

	if (!new)
		return ;
	if (!*head)
		*head = new;
	else
	{
		tmp = tkn_last(*head);
		tmp->next = new;
	}
}

static t_token	*tkn_new(const char *data, int len, t_states type)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->token = ft_strndup(data, len);
	if (!token->token)
	{
		free(token);
		return (NULL);
	}
	token->type = type;
	token->next = NULL;
	token->expanded = 0;
	return (token);
}

void	fill_token(char *cmd, t_token **fill)
{
	t_token		*new;
	t_lexer		lexer;
	t_states	token;

	lexer.content = cmd;
	lexer.quote_state = QUOTES_NONE;
	token = next_token(&lexer);
	while (token != MST_EOF)
	{
		new = tkn_new(lexer.token.str, lexer.token.len, token);
		if (!new)
			return (free_tkn(fill));
		tkn_addback(fill, new);
		token = next_token(&lexer);
	}
}
