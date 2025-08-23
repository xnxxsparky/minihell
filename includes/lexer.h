/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <bcausseq@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 23:56:33 by bcausseq          #+#    #+#             */
/*   Updated: 2025/08/23 22:21:43 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LEXER_H
# define LEXER_H

# include "../libft/includes/libft.h"
# include <math.h>
# include <readline/history.h>
# include <stdio.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>

/*ENUMS NEEDED*/

typedef enum e_states
{
	MST_WORD,
	MST_REDIR,
	MST_PIPE,
	MST_EXPAND,
	MST_EOF
}	t_states;

typedef enum e_quotes
{
	QUOTES_NONE,
	SIMPLE_QUOTES,
	DOUBLE_QUOTES
}	t_quotes;

/*CORE OF THE LEXER*/

typedef struct s_strview
{
	const char	*str;
	uint64_t	len;
}	t_strview;

typedef struct s_lexer
{
	const char	*content;
	t_strview	token;
	t_quotes	quote_state;
}	t_lexer;

typedef struct s_token
{
	char			*token;
	t_states		type;
	int				expanded;
	struct s_token	*next;
}	t_token;

//LEXER TOKEN FUNCTIONS
t_states
token_redir(t_lexer *lexer);

t_states
token_pipe(t_lexer *lexer);

t_states
token_expand(t_lexer *lexer);

t_states
token_word(t_lexer *lexer);

//LEXER UTILS
char
lexer_get_char(t_lexer *lexer);

void
lexer_advance(t_lexer *lexer, int len);

void
skip_spaces(t_lexer *lexer);

char
lexer_peek(t_lexer *lexer);

void
lexer_token(t_lexer *lexer, int len);

//TOKEN MANAGEMENT
void
free_tkn(t_token **cmd);

void
fill_token(char *cmd, t_token **fill);

void
quotes_rm(t_token **cmd);

//LEXER HELPER
void
lexer_get_var(t_lexer *lexer);

void
lexer_get_word(t_lexer *lexer);

t_states
next_token(t_lexer *lexer);

bool
cond_break_wd(char c, t_lexer *lexer);

#endif
