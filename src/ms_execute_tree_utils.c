/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_tree_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 06:18:35 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/06/02 01:29:25 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_free_path(t_path *path)
{
	t_path	*tmp;

	tmp = path;
	if (!path)
	{
		return ;
	}
	while (path)
	{
		tmp = path;
		path = path->next;
		free(tmp);
	}
}

static size_t	lis_len(t_path *node)
{
	size_t	len;

	len = 0;
	if (!node)
	{
		return (len);
	}
	while (node->next)
	{
		len++;
		node = node->next;
	}
	return (len);
}

void	ms_waitpid(int pid, t_info *info)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WSTOPSIG(status) == 1)
	{
		info->status = 1;
	}
	else if (WSTOPSIG(status) != 1)
	{
		info->status = 0;
	}
}

static void	init_pipe(char token, t_info *info)
{
	if (token == PIPE)
	{
		info->pipe = 1;
		pipe(info->fd);
	}
}

static void	end_execution(t_info *info, int pid, char token, t_path *path)
{
	if (token == PIPE)
	{
		close(info->fd[1]);
		dup2(info->fd[0], 0);
		dup2(info->stdin_clone, info->fd[0]);
		close(info->fd[0]);
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
	ms_free_path(path);
}

static void	init_pipe_child(t_node *node, t_info *info)
{
	if (node->token == PIPE)
	{
		close(info->fd[0]);
		dup2(info->fd[1], 1);
	}
}

static void	end_execution_child(t_node *node, t_info *info, t_path *path)
{

	write(2, "Error: command not found: ", 26);
	write(2, node->cmd->args[0], ft_strlen(node->cmd->args[0]));
	write(2, "\n", 1);
	if (node->token == PIPE)
	{
		close(info->fd[1]);
	}
	ms_free(info->root, info);
	ms_free_path(path);
	/// file descriptors ///
	exit(1);
}

int	ms_execute_cmd(t_node *node, t_cmd *cmd, t_info *info, t_path *path)
{
	pid_t	pid;
	int		paths_len;
	int		i;

	init_pipe(node->token, info);
	pid = fork();
	if (pid == 0)
	{
		init_pipe_child(node, info);
		paths_len = lis_len(path);
		i = 0;
		while (i < paths_len)
		{
			execve(path->str, cmd->args, info->env);
			path = path->next;
			i++;
		}
		end_execution_child(node, info, path);
	}
	end_execution(info, pid, node->token, path);
	return (info->status);
}
