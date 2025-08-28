/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <bcausseq@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 04:31:17 by bcausseq          #+#    #+#             */
/*   Updated: 2025/08/28 19:16:12 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

void	free_cmd_dec(t_cmd **cmd_dec)
{
	int	i;

	i = 0;
	while ((*cmd_dec)[i].cmd)
	{
		free((*cmd_dec)[i].path);
		free((*cmd_dec)[i].cmd);
		i++;
	}
	free(*cmd_dec);
}

void	closed(t_shell *shel, int index)
{
	if (!shel->cmd_dec[index + 1].cmd)
	{
		close(3);
		close(4);
	}
	return ;
}

void	ft_exit(t_shell *shel, int index)
{
	int			ret;
	const char	*code;

	code = shel->cmd_dec[index].cmd[1];
	if (code && shel->cmd_dec[index].cmd[2])
	{
		ft_fprintf(2, "minihell: exit: too many arguments\n");
		shel->retcode = 1;
		return ;
	}
	if (!code)
		ret = shel->retcode;
	else
		ret = ft_atoll(code);
	if (errno == ERANGE)
	{
		ft_fprintf(2, "minihell: exit: %s: numeric argument required\n", code);
		ret = 2;
	}
	closed(shel, index);
	free_free(shel);
	exit(ret);
}

	/////////////////////////////

// 	int		ret;
// 	bool	ret_need;
// 
// 	ret_need = false;
// 	if (!ft_isdigit_while(shel->cmd_dec[index].cmd[1])
// 		&& shel->cmd_dec[index].cmd[2])
// 	{
// 		ft_fprintf(2, "minihell: exit: too many arguments\n");
// 		shel->retcode = 1;
// 		return ;
// 	}
// 	else if (shel->cmd_dec[index].cmd[1])
// 	{
// 		ret = ft_atoll(shel->cmd_dec[index].cmd[1]);
// 		ret_need = true;
// 	}
// 	full_free(shel, &ret_need, &ret, index);
// 	if (ret_need)
// 		exit(ret);
// 	exit(shel->retcode);
// }
