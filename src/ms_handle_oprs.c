/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_handle_oprs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 20:52:41 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/06/01 23:54:56 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_fd	*create_fd_node(t_fd *node)
{
	t_fd	*new;

	new = ft_calloc(1, sizeof(t_fd));
	new->fd = 0;
	new->fd_clone = 0;
	new->file_fd = 0;
	new->next = NULL;
	if (node)
	{
		node->next = new;
	}
	return (new);
}

int	ms_handle_oprs(t_info *info, t_opr *opr, t_fd *fd_node)
{
	while (opr)
	{
		fd_node->fd = opr->fd;
		fd_node->fd_clone = dup(opr->fd);
		fd_node->file_fd = open(opr->arg, O_RDWR);
		if (fd_node->file_fd == -1)
		{
			write(2, "Error: bad path file.\n", 22);
			info->status = 1;
			return (1);
		}
		dup2(fd_node->file_fd, fd_node->fd);
		opr = opr->next;
		if (!opr)
		{
			break ;
		}
		fd_node = create_fd_node(fd_node);
	}
	info->status = 0;
	return (0);
}
