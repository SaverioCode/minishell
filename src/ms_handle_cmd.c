/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_handle_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 07:02:15 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/06/05 17:09:11 by fgarzi-c         ###   ########.fr       */
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

static char	**format_cmd_args(char *cmd, char **args)
{
	char	**new;
	int		len;
	int		i;

	len = ft_biarrlen(args);
	if (!len)
	{
		new = ft_calloc(2, 8);
		new[0] = ft_strjoin(cmd, NULL, 0, 0);
		return (new);
	}
	new = ft_calloc(len + 2, 8);
	new[0] = ft_strjoin(cmd, NULL, 0, 0);
	i = 0;
	while (args[i])
	{
		new[1 + i] = args[i];
		i++;
	}
	free(args);
	return (new);
}

int	ms_execute_cmd(t_node *node, t_cmd *cmd, t_info *info, t_path *path)
{
	pid_t	pid;
	int		paths_len;
	int		i;

	ms_init_pipe(node->token, info);
	pid = fork();
	if (pid == 0)
	{
		ms_init_pipe_child(node, info);
		paths_len = lis_len(path);
		i = 0;
		while (i < paths_len)
		{
			execve(path->str, cmd->args, info->env);
			path = path->next;
			i++;
		}
		info->status = 1;
		//// write command error ////
		write(2, "Error: command not found: \n", 27);
		ms_end_execution_child(node, info, path);
	}
	ms_end_execution(node->token, info, pid, path);
	return (info->status);
}

void	ms_handle_cmd(t_node *node, t_info *info, t_fd *fd_lis)
{
	t_path	*path;

	if (node->cmd == NULL)
	{
		return ;
	}
	if (node->token == PIPE && check_fd_lis(fd_lis))
	{
		node->token = 0;
	}
	path = NULL;
	path = create_path_node(path);
	get_cmd_paths(path, info->env, node->cmd->cmd);
	node->cmd->args = format_cmd_args(node->cmd->cmd, node->cmd->args);
	info->status = ms_execute_cmd(node, node->cmd, info, path);
}
