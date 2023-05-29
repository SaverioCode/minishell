/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 08:12:12 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/29 11:32:34 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_tinfo(t_info *info, char **env)
{
	int	len;
	int	i;

	info->env = NULL;
	len = ft_biarrlen(env);
	info->env = ft_calloc(len + 1, 8);
	i = 0;
	while (env[i])
	{
		info->env[i] = ft_strjoin(env[i], NULL, 0, 0);
		i++;
	}
	info->input = NULL;
	info->stdin_clone = 0;
	info->stdout_clone = 0;
	info->status = 0;
	info->prompt = NULL;
}

void	init_tcmd(t_cmd *node)
{
	node->cmd = NULL;
	node->args = NULL;
}

void	init_topr(t_opr *node)
{
	node->token = 0;
	node->fd = 0;
	node->arg = NULL;
	node->next = NULL;
}

void	init_tnode(t_node *node)
{
	node->token = 0;
	node->opr = NULL;
	node->cmd = NULL;
	node->subshl = NULL;
	node->next = NULL;
	node->back = NULL;
}
