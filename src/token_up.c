/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <bcausseq@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 20:23:07 by bcausseq          #+#    #+#             */
/*   Updated: 2025/08/23 22:22:56 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

// void	print(t_token *cmd, char *c)
// {
// 	t_token	*cur;
// 
// 	if (!cmd)
// 		return ;
// 	cur = cmd;
// 	while (cur)
// 	{
// 		printf("%s%s\n%s", c, cur->token, RESET);
// 		cur = cur->next;
// 	}
// }

t_token	*no_dol(t_token *del, t_token **cmd)
{
	t_token	*cur;

	cur = *cmd;
	if (del == *cmd)
	{
		*cmd = (*cmd)->next;
		cur = *cmd;
	}
	else
	{
		while (cur->next && cur->next != del)
			cur = cur->next;
		cur->next = cur->next->next;
	}
	tkn_delone(del);
	return (cur);
}

t_token	*update_list(t_token *del, t_token **cmd)
{
	t_token	*cur;
	t_token	*new;

	new = NULL;
	fill_token(del->token, &new);
	if (!new)
		return (no_dol(del, cmd));
	cur = *cmd;
	if (del == *cmd)
	{
		*cmd = new;
		cur = *cmd;
		cur = tkn_lst(cur);
		cur->next = del->next;
	}
	else
	{
		while (cur->next && cur->next != del)
			cur = cur->next;
		cur->next = new;
		cur = tkn_lst(cur);
		cur->next = del->next;
	}
	tkn_delone(del);
	return (cur);
}

void	update_xpd(t_shell *shel, t_token **cmd, t_token **cur)
{
	t_states	old;

	if ((*cur) && ((*cur)->type == MST_WORD || (*cur)->type == MST_EXPAND))
	{
		replace(shel, (*cur)->token, &((*cur)->token));
		if (!(*cur)->token)
			return ;
		old = (*cur)->type;
		(*cur) = update_list((*cur), cmd);
		if (*cur && ((*cur)->type) != MST_EXPAND)
			(*cur)->expanded = (old == MST_EXPAND);
	}
	if (*cur)
		(*cur) = (*cur)->next;
}

void	update_token(t_shell *shel, t_token **cmd)
{
	t_token	*cur;

	cur = *cmd;
	while (cur)
	{
		if (ft_strncmp(cur->token, "<<", 2) == 0)
		{
			if (!cur->next)
				return ;
			cur = cur->next->next;
		}
		else if (!ft_strcmp(cur->token, "$"))
		{
			cur->type = MST_WORD;
			cur = cur->next;
		}
		else
			update_xpd(shel, cmd, &cur);
	}
}
