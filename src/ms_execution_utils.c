/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execution_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 06:18:35 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/07/17 11:33:24 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_check_fd_lis(t_fd *fd_lis, int fd)
{
	while (fd_lis)
	{
		if (fd_lis->fd == fd)
		{
			return (0);
		}
		fd_lis = fd_lis->next;
	}
	return (-1);
}

void	ms_init_pipe(char token, t_info *info)
{
	if (info->pipe == 1)
	{
		dup2(info->fd[0], 0);
		close(info->fd[0]);
	}
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
		if (ms_check_fd_lis(info->fd_lis, 1) == 0)
		{
			close(info->fd[1]);
			return ;
		}
		dup2(info->fd[1], 1);
	}
}

void	ms_end_execution(char token, t_info *info, pid_t pid)
{
	if (token == PIPE)
	{
		close(info->fd[1]);
		ms_store_pid(info, pid);
	}
	else
	{
		ms_waitpid(pid, info);
	}
}

void	ms_end_execution_child(t_info *info)
{
	if (info->pipe == 1)
	{
		close(info->fd[1]);
	}
	exit(info->status);
}
