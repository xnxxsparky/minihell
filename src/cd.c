/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypoulett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 02:25:33 by ypoulett          #+#    #+#             */
/*   Updated: 2025/09/02 19:11:44 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

static char	*path_creator(t_shell *shel, t_env *search, int index)
{
	char	*first_path;
	char	*second_path;
	char	*final_path;

	first_path = ft_strndup(search->value, ft_strlen(search->value));
	second_path = ft_strchr(shel->cmd_dec[index].cmd[1], '~');
	if (!second_path)
	{
		free(first_path);
		return (ft_strdup(search->value));
	}
	second_path = ft_strdup(second_path + 1);
	if (!second_path)
	{
		free(first_path);
		return (ft_strdup(search->value));
	}
	second_path[ft_strlen(second_path) - 1] = '\0';
	if (first_path && second_path)
	{
		final_path = ft_strjoin(first_path, second_path, 1, 1);
		return (final_path);
	}
	return (NULL);
}

static void	tild_expander(t_shell *shel, int index)
{
	t_env	*search;
	char	*final_path;

	search = env_finder(shel->env, "HOME");
	if (search)
	{
		final_path = path_creator(shel, search, index);
		if (final_path)
		{
			if (access(final_path, R_OK) == 0)
			{
				chdir(final_path);
				env_addedit(&(shel->env), "PWD", final_path);
				free(final_path);
				shel->retcode = 0;
				return ;
			}
		}
	}
	ft_fprintf(2, "minihell: cd: HOME not set\n");
	shel->retcode = 1;
}

void	ft_cd(t_shell *shel, int index)
{
	if (array_len(shel->cmd_dec[index].cmd) >= 3)
	{
		ft_fprintf(2, "minihell: cd: too many arguments\n");
		shel->retcode = 1;
		return ;
	}
	env_addedit(&(shel->env), "OLDPWD", get_pwd());
	if (!shel->cmd_dec[index].cmd[1] || shel->cmd_dec[index].cmd[1][0] == '~')
		tild_expander(shel, index);
	else if (access(shel->cmd_dec[index].cmd[1], R_OK) == 0)
	{
		chdir(shel->cmd_dec[index].cmd[1]);
		env_addedit(&(shel->env), "PWD", get_pwd());
		shel->retcode = 0;
	}
	else
	{
		ft_fprintf(2, "cd: %s: No such file or directory\n",
			shel->cmd_dec[index].cmd[1]);
		shel->retcode = 1;
	}
}
