/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_tree_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 06:18:35 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/06/01 18:40:48 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ms_execute_cmd(t_cmd *cmd, t_info *info, t_path *path)
{
	pid_t	pid;
	int		paths_len;
	int		i;

	pid = fork();
	if (pid == 0)
	{
		paths_len = lis_len(path);
		i = 0;
		while (i < paths_len)
		{
			execve(path->str, cmd->args, info->env);
			path = path->next;
			i++;
		}
		write(2, "Error: command not found: ", 26);
		write(2, cmd->args[0], ft_strlen(cmd->args[0]));
		write(2, "\n", 1);
		exit(1);
	}
	ms_waitpid(pid, info);
	if (info->pipe)
	{
		dup2(info->stdin_clone, 0);
		info->pipe = 0;
	}
	return (info->status);
}

int	ms_execute_cmd_pipe(t_cmd *cmd, t_info *info, t_path *path)
{
	pid_t	pid;
	int		paths_len;
	int		i;

	if (info->pipe)
	{
		dup2(info->stdin_clone, info->fd[0]);
	}
	info->pipe = 1;
	pipe(info->fd);

	pid = fork();
	if (pid == 0)
	{
		close(info->fd[0]);
		dup2(info->fd[1], 1);
		paths_len = lis_len(path);
		i = 0;
		while (i < paths_len)
		{
			execve(path->str, cmd->args, info->env);
			path = path->next;
			i++;
		}
		write(2, "Error: command not found: \n", 27);
		exit(1);
	}

	close(info->fd[1]);
	dup2(info->fd[0], 0);
	
	ms_waitpid(pid, info);

	close(info->fd[0]);
	
	return (info->status);
}
