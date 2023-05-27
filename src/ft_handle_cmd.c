/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 07:02:15 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/27 15:09:27 by fgarzi-c         ###   ########.fr       */
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

int	ft_handle_cmd(t_node *node, t_info *info)
{
	t_path	*path;

	if (node->cmd == NULL)
	{
		return (0);
	}
	path = NULL;
	path = create_path_node(path);
	get_cmd_paths(path, info->env, node->cmd->cmd);
	if (ft_execute_cmd(node->cmd, info, path, node->token) == -1)
	{
		ft_free_path(path);
		return (-1);
	}
	ft_free_path(path);
	return (0);
}
