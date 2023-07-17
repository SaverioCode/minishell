/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init_structs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sav <sav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 08:12:12 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/07/17 06:44:29 by sav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_init_tpid(t_child *child)
{
	child->pid = 0;
	child->next = NULL;
}

void	ms_init_tcmd(t_cmd *node)
{
	node->cmd = NULL;
	node->args = NULL;
}

void	ms_init_topr(t_opr *node)
{
	node->token = 0;
	node->fd = 0;
	node->path = NULL;
	node->arr = NULL;
	node->next = NULL;
}

void	ms_init_tnode(t_node *node)
{
	node->token = 0;
	node->opr = NULL;
	node->cmd = NULL;
	node->subshl = NULL;
	node->next = NULL;
	node->back = NULL;
}

void	ms_init_tinfo(t_info *info, char **env)
{
	info->root = NULL;
	info->child = NULL;
	info->fd_lis = NULL;
	ms_set_env(info, env);
	info->token = 0;
	info->input = NULL;
	info->stdin_clone = 0;
	info->stdin_clone = dup(0);
	info->stdout_clone = 0;
	info->stdout_clone = dup(1);
	info->status = 0;
	info->exit_status = 0;
	info->prompt = NULL;
	info->pipe = 0;
	info->subshl = 0;
}
