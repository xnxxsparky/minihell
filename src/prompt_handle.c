/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypoulett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 03:22:05 by ypoulett          #+#    #+#             */
/*   Updated: 2025/08/16 03:46:22 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

char	*join3(char *str1, char *str2, char *str3, int opt)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(str1, str2, (opt & 1), (opt & 2) >> 1);
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, str3, 1, 0);
	if (!result)
		return (NULL);
	return (result);
}

void	prompt_initializer(t_shell *shel, char **prompt)
{
	t_env	*log;
	char	buf[4096];

	ft_bzero(buf, 4096);
	log = env_finder(shel->env, "LOGNAME");
	if (!log)
		*prompt = join3(CYAN_IGNORED, "Guest", " ", 0);
	else
		*prompt = join3(CYAN_IGNORED, log->value, " ", 0);
	if (!prompt)
		return ;
	getcwd(buf, 4096);
	*prompt = join3(*prompt, MAGENTA_IGNORED, ft_strrchr(buf, '/'), 1);
	if (!prompt)
		return ;
	*prompt = join3(*prompt, RESET_IGNORED, " > ", 1);
	if (!prompt)
		return ;
}

// void	prompt_initializer(t_shell *shel, char **prompt)
// {
// 	t_env	*log;
// 
// 	log = env_finder(shel->env, "LOGNAME");
// 	*prompt = ft_strjoin(RL_START_IGNORE, CYAN, 0, 0);
// 	*prompt = ft_strjoin(*prompt, RL_END_IGNORE, 1, 0);
// 	if (!log)
// 		*prompt = ft_strjoin(*prompt, "Guest", 1, 0);
// 	else
// 		*prompt = ft_strjoin(*prompt, log->value, 1, 0);
// 	*prompt = ft_strjoin(*prompt, " ", 1, 0);
// 	*prompt = ft_strjoin(*prompt, RL_START_IGNORE, 1, 0);
// 	*prompt = ft_strjoin(*prompt, MAGENTA, 1, 0);
// 	*prompt = ft_strjoin(*prompt, RL_END_IGNORE, 1, 0);
// 	log = env_finder(shel->env, "PWD");
// 	if (!log)
// 		*prompt = ft_strjoin(*prompt, "/NULL", 1, 0);
// 	else
// 		*prompt = ft_strjoin(*prompt, ft_strrchr(log->value, '/'), 1, 0);
// 	*prompt = ft_strjoin(*prompt, RL_START_IGNORE, 1, 0);
// 	*prompt = ft_strjoin(*prompt, RESET, 1, 0);
// 	*prompt = ft_strjoin(*prompt, RL_END_IGNORE, 1, 0);
// 	*prompt = ft_strjoin(*prompt, " > ", 1, 0);
// }
