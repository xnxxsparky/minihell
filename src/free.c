/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <bcausseq@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 20:37:39 by bcausseq          #+#    #+#             */
/*   Updated: 2025/08/11 20:38:10 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minihell.h"

void	free_free(t_shell *shel)
{
	free(shel->cmd_user);
	free(shel->prompt);
	env_lstclear(&(shel->env));
	free(shel->env);
	free_cmd_dec(&(shel->cmd_dec));
	free_spl((void **)shel->env_ar);
	free_tkn(&(shel->cmd));
}
