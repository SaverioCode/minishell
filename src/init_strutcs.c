/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_strutcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 08:12:12 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/17 18:40:06 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_tenv(t_env *node)
{
	node->name = NULL;
	node->value = NULL;
	node->next = NULL;
}

void	init_tinfo(t_info *info)
{
	info->env = NULL;
	info->status = 0;
	info->input = NULL;
}

void	init_tcmd(t_cmd *node)
{
	node->cmd = NULL;
	node->args = NULL;
}

void	init_topr(t_opr *node)
{
	node->fd = NULL;
	node->arg = NULL;
	node->next = NULL;
}

void	init_tnode(t_node *node)
{
	node->shlvl = 0;
	node->token = 0;
	node->fd_output = 0;
	node->exp = NULL;
	node->cmd = NULL;
	node->opr = NULL;
	node->subshl = NULL;
	node->next = NULL;
	node->back = NULL;
}
