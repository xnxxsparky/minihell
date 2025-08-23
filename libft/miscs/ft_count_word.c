/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <bcausseq@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 04:27:55 by bcausseq          #+#    #+#             */
/*   Updated: 2025/05/31 23:51:20 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_words(char const *s, char c)
{
	int	i;
	int	word;

	if (!s || !*s)
		return (0);
	word = 0;
	i = 0;
	if (s && s[i] != c)
		word++;
	i = 1;
	while (s && i[s])
	{
		while ((i[s] == c) && (i[s]))
			i++;
		while ((i[s] != c) && (i[s]))
		{
			if (s[i - 1] == c)
				word++;
			i++;
		}
	}
	return (word);
}
