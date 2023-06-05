/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_handle_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 07:02:15 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/06/05 20:07:48 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_fd_lis(t_fd *fd_lis)
{
	while (fd_lis)
	{
		if (fd_lis->fd == 1)
		{
			return (1);
		}
		fd_lis = fd_lis->next;
	}
	return (0);
}

static int	ms_execute_cmd(t_node *node, t_cmd *cmd, t_info *info)
{
	pid_t	pid;

	ms_init_pipe(node->token, info);
	pid = fork();
	if (pid == 0)
	{
		ms_init_pipe_child(node, info);
		execve(cmd->cmd, cmd->args, info->env);
		info->status = 1;
		//// write command error ////
		write(2, "Error: command not found: \n", 27);
		ms_end_execution_child(node, info);
	}
	ms_end_execution(node->token, info, pid);
	return (info->status);
}

void	ms_handle_cmd(t_node *node, t_info *info, t_fd *fd_lis)
{
	if (node->cmd == NULL)
	{
		return ;
	}
	if (node->token == PIPE && check_fd_lis(fd_lis))
	{
		node->token = 0;
	}
	ms_format_cmd(node->cmd, info->env);
	info->status = ms_execute_cmd(node, node->cmd, info);
}
