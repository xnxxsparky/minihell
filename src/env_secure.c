/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_secure.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypoulett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 03:32:19 by ypoulett          #+#    #+#             */
/*   Updated: 2025/09/05 04:39:17 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

char	*get_pwd(void)
{
	static char	buf[4096];

	if (getcwd(buf, sizeof(buf)))
		return (buf);
	return ("");
}

static char	*get_home(void)
{
	struct dirent	*d;
	DIR				*dir;
	char			*path;

	dir = opendir("/home");
	d = readdir(dir);
	while (d)
	{
		path = ft_strjoin("/home/", d->d_name, 0, 0);
		if (!path)
			return (NULL);
		if (access(path, O_RDWR) == 0)
		{
			closedir(dir);
			return (path);
		}
		d = readdir(dir);
		free(path);
	}
	closedir(dir);
	return (NULL);
}

void	env_lstclear(t_env **env)
{
	t_env	*tmp;
	t_env	*curr;

	if (!env || !*env)
		return ;
	curr = *env;
	while (curr)
	{
		tmp = curr->next;
		free(curr->name);
		curr->name = NULL;
		if (curr->value)
			free(curr->value);
		curr->value = NULL;
		curr->next = NULL;
		free(curr);
		curr = tmp;
	}
	free(curr);
	*env = NULL;
}

void	env_secure(t_env **newenv)
{
	char	*home;

	(*newenv) = env_instantiate(NULL);
	home = get_home();
	env_addedit(newenv, "HOME", home);
	free(home);
	env_addedit(newenv, "OLDPWD", get_pwd());
	env_addedit(newenv, "PWD", get_pwd());
	env_addedit(newenv, "SHLVL", "1");
}
