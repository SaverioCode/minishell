/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_handle_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 07:02:15 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/06/01 18:09:23 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free_path(t_path *path)
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

int	ms_handle_cmd(t_node *node, t_info *info, t_fd *fd_lis)
{
	t_path	*path;

	if (node->cmd == NULL)
	{
		return (0);
	}
	if (node->token == PIPE && check_fd_lis(fd_lis))
	{
		node->token = AND;
	}
	path = NULL;
	path = create_path_node(path);
	get_cmd_paths(path, info->env, node->cmd->cmd);
	node->cmd->args = format_cmd_args(node->cmd->cmd, node->cmd->args);
	if (node->token == PIPE)
	{
		ms_execute_cmd_pipe(node->cmd, info, path);
		ft_free_path(path);
		return (0);
	}
	else if (ms_execute_cmd(node->cmd, info, path) == 0)
	{
		ft_free_path(path);
		return (0);
	}
	ft_free_path(path);
	return (1);
}
