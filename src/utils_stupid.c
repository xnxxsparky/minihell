/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_stupid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <bcausseq@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 02:29:20 by bcausseq          #+#    #+#             */
/*   Updated: 2025/08/27 21:38:34 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

char	*joinwhile(char *recep, char *to_add)
{
	char	*ret;

	ret = ft_strjoin(recep, "=", 1, 0);
	if (!ret)
		return (NULL);
	ret = ft_strjoin(ret, to_add, 1, 0);
	if (!ret)
		return (NULL);
	return (ret);
}

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
