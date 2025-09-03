/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <bcausseq@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 01:58:32 by bcausseq          #+#    #+#             */
/*   Updated: 2025/09/03 19:39:27 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

static bool	good_quotes(char *src)
{
	int		i;
	char	to_find;

	i = 0;
	while (src[i])
	{
		if (src[i] == '\'' || src[i] == '"')
		{
			to_find = src[i];
			i++;
			while (src[i] && src[i] != to_find)
				i++;
			if (src[i] != to_find)
				return (false);
		}
		i++;
	}
	return (true);
}

bool	is_line_valid(t_shell *shel, char *src)
{
	if (!src)
	{
		free(shel->prompt);
		env_lstclear(&(shel->env));
		free(shel->env);
		free_spl((void **)shel->env_ar);
		write(1, "exit\n", 5);
		rl_clear_history();
		exit(shel->retcode);
	}
	if (good_quotes(src) == false)
		return (false);
	return (true);
}
