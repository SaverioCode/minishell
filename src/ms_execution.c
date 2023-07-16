/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sav <sav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 11:15:31 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/07/16 12:02:01 by sav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_restore_fd(t_info *info)
{
	t_fd	*fd_lis;
	t_fd	*tmp;

	fd_lis = info->fd_lis;
	while (fd_lis)
	{
		if (fd_lis->file_fd != 0)
		{
			dup2(fd_lis->fd_clone, fd_lis->fd);
			close(fd_lis->fd_clone);
			close(fd_lis->file_fd);
		}
		tmp = fd_lis;
		fd_lis = fd_lis->next;
		free(tmp);
	}
	info->fd_lis = NULL;
}

static int	ms_check_status(t_info *info)
{
	if (info->status == 0)
	{
		if (info->token == AND || info->token == PIPE || !info->token)
		{
			return (0);
		}
	}
	else if (info->status > 0)
	{
		if (info->token == OR || info->token == PIPE)
		{
			return (0);
		}
	}
	return (1);
}

static t_node	*get_next_node(t_node *node, t_info *info)
{
	if (node == NULL)
	{
		return (NULL);
	}
	while (node)
	{
		info->token = node->token;
		if (ms_check_status(info) == 0)
		{
			return (node->next);
		}
		node = node->next;
	}
	return (node);
}

static void	check_subshell(t_node *node, t_info *info)
{
	pid_t	pid;

	if (node == NULL)
	{
		return ;
	}
	if (node->subshl)
	{
		pid = fork();
		if (pid == 0)
		{
			ms_init_pipe_child(node, info);
			info->subshl = 1;
			ms_execute_tree(node->subshl, info);
			ms_end_execution_child(info);
		}
		ms_end_execution(node->token, info, pid);
	}
}

void	ms_execute_tree(t_node *node, t_info *info)
{
	while (node)
	{
		ps_expander(node, info);
		ms_init_pipe(node->token, info);
		if (ms_handle_oprs(info, node, node->opr, info->fd_lis) == 0)
		{
			ms_handle_cmd(node, info);
		}
		check_subshell(node, info);
		node = get_next_node(node, info);
		ms_restore_fd(info);
	}
	ms_waitchild(info);
}
