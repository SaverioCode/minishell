/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execution_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 06:18:35 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/06/05 19:39:19 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_init_pipe(char token, t_info *info)
{
	if (token == PIPE)
	{
		info->pipe = 1;
		pipe(info->fd);
	}
}

void	ms_init_pipe_child(t_node *node, t_info *info)
{
	if (node->token == PIPE)
	{
		close(info->fd[0]);
		dup2(info->fd[1], 1);
	}
}

void	ms_end_execution(char token, t_info *info, pid_t pid)
{
	if (token == PIPE)
	{
		close(info->fd[1]);
		dup2(info->fd[0], 0);
		dup2(info->stdin_clone, info->fd[0]);
		close(info->fd[0]);
		ms_store_pid(info, pid);
	}
	else
	{
		ms_waitpid(pid, info);
		if (info->pipe)
		{
			dup2(info->stdin_clone, 0);
			info->pipe = 0;
		}
	}
}

void	ms_end_execution_child(t_node *node, t_info *info)
{
	if (node->token == PIPE)
	{
		close(info->fd[1]);
	}
	ms_free(info->root, info);
	/// file descriptors ///
	exit(info->status);
}
