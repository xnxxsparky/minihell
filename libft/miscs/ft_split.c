/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 02:41:46 by bcausseq          #+#    #+#             */
/*   Updated: 2025/05/31 04:27:44 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_words(char **src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		free(src[i]);
		i++;
	}
	free(src);
}

static void	word_split(char const *s, char c, size_t *deb, size_t *end)
{
	while ((s[*deb] == c) && (s[*deb]))
		*deb = *deb + 1;
	*end = *deb;
	while ((s[*end] != c) && (s[*end]))
		*end = *end + 1;
}

static char	**str_cut(char const *s, char c, char **ret)
{
	size_t	i;
	size_t	j;
	int		words;

	i = 0;
	j = 0;
	words = 0;
	while (s && (j < ft_strlen(s)))
	{
		word_split(s, c, &i, &j);
		if (i != j)
		{
			ret[words] = ft_substr(s, i, j - i);
			if (!ret[words])
			{
				free_words(ret);
				return (NULL);
			}
			j++;
			words++;
			i = j;
		}
	}
	ret[count_words(s, c)] = NULL;
	return (ret);
}

char	**ft_split(char const *s, char c)
{
	char	**ret;

	if (!s)
		return (NULL);
	if (!*s)
		return (ft_calloc(1, sizeof(char *)));
	ret = ft_calloc(count_words(s, c) + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	return (str_cut(s, c, ret));
}
