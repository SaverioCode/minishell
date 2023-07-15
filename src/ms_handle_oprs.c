/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_handle_oprs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 20:52:41 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/07/15 23:24:57 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_fd	*create_fd_node(t_info *info, t_fd *node)
{
	t_fd	*new;

	new = ft_calloc(1, sizeof(t_fd));
	new->fd = 0;
	new->fd = -1;
	new->fd_clone = 0;
	new->file_fd = 0;
	new->next = NULL;
	if (node)
	{
		node->next = new;
	}
	else
	{
		info->fd_lis = new;
	}
	return (new);
}

t_fd	*get_fd_node(t_fd *head, t_fd *target)
{
	t_fd	*fd_node;

	fd_node = head;
	while (fd_node)
	{
		if (fd_node->next == target)
		{
			return (fd_node);
		}
		fd_node = fd_node->next;
	}
	return (NULL);
}

void	ms_check_fd(t_opr *opr, t_info *info)
{
	t_fd	*fd_node;
	t_fd	*var;

	fd_node = info->fd_lis;
	while (fd_node)
	{
		if (opr->fd == fd_node->fd)
		{
			dup2(fd_node->fd_clone, fd_node->fd);
			close(fd_node->fd_clone);
			close(fd_node->file_fd);
			if (fd_node == info->fd_lis)
			{
				free(fd_node);
				info->fd_lis = NULL;
				return ;
			}
			var = get_fd_node(info->fd_lis, fd_node);
			var->next = fd_node->next;
			free(fd_node);
			return ;
		}
		fd_node = fd_node->next;
	}
}

int	ms_handle_oprs(t_info *info, t_opr *opr, t_fd *fd_node)
{
	while (opr)
	{
		ms_check_fd(opr, info);
		fd_node = create_fd_node(info, get_fd_node(info->fd_lis, NULL));
		if (opr->token == OUT || opr->token == APP)
		{
			if (ms_output_redir(opr, fd_node) == 1)
				return (1);
		}
		else if (opr->token == INP || opr->token == HDOC)
		{
			if (ms_input_redir(info, opr, fd_node) == 1)
				return (1);
		}
		opr = opr->next;
	}
	info->status = 0;
	info->exit_status = info->status;
	return (0);
}
