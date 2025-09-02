/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_stupid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <bcausseq@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 02:29:20 by bcausseq          #+#    #+#             */
/*   Updated: 2025/09/02 19:45:49 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

void	free_spl(void **s)
{
	int	i;

	i = -1;
	while (s[++i])
		free(s[i]);
	free(s);
}

int	env_len(t_env *env)
{
	int		i;
	t_env	*curr;

	i = 0;
	curr = env;
	if (!env)
		return (i);
	while (curr->next)
	{
		curr = curr->next;
		i++;
	}
	return (i);
}

int	array_len(char **array)
{
	int	i;

	if (!array)
		return (0);
	i = 0;
	while (array[i])
		i++;
	return (i);
}
