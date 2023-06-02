/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_handle_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 07:02:15 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/06/02 01:09:15 by fgarzi-c         ###   ########.fr       */
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
