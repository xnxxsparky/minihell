/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <bcausseq@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 22:08:04 by bcausseq          #+#    #+#             */
/*   Updated: 2025/08/23 22:08:45 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

t_token	*tkn_lst(t_token *tkn)
{
	t_token	*cur;

	if (!tkn)
		return (NULL);
	cur = tkn;
	while (cur->next)
		cur = cur->next;
	return (cur);
}

void	tkn_delone(t_token *del)
{
	free(del->token);
	free(del);
}
