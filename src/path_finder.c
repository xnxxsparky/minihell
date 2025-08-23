/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <bcausseq@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 01:58:15 by bcausseq          #+#    #+#             */
/*   Updated: 2025/08/23 18:38:17 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

char	*finder_while(char *src, char **pot_path)
{
	char	path[4096];
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (pot_path[++i])
	{
		ft_bzero(path, sizeof(path));
		ft_strcat(path, pot_path[i]);
		ft_strcat(path, "/");
		ft_strcat(path, src);
		if (access(path, F_OK) == 0)
		{
			while (pot_path[++j])
				free(pot_path[j]);
			free(pot_path);
			return (ft_strdup(path));
		}
	}
	while (pot_path[++j])
		free(pot_path[j]);
	free(pot_path);
	return (NULL);
}

char	*path_finder(char *src, char *path)
{
	char	**pot_path;
	char	*path_finded;

	pot_path = ft_split(path, ':');
	if (!pot_path)
		return (NULL);
	path_finded = finder_while(src, pot_path);
	return (path_finded);
}

void	parse(t_shell *shel, char *src, char **bin)
{
	char	*cmd;
	t_env	*path;

	if (access(src, F_OK) == 0)
	{
		*bin = ft_strdup(src);
		return ;
	}
	path = env_finder(shel->env, "PATH");
	if (!src || ft_strlen(src) >= 4096 || path == NULL)
	{
		*bin = NULL;
		return ;
	}
	cmd = path_finder(src, path->value);
	*bin = cmd;
}
