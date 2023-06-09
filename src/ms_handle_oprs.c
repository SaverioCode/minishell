/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_handle_oprs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 20:52:41 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/06/09 18:29:32 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_fd	*create_fd_node(t_fd *node)
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
	return (new);
}

// int	here_document(t_info *info, t_opr *opr, t_fd *fd_node)
// {
// 	char	*buffer;
// 	int
// }

int	ms_handle_oprs(t_info *info, t_opr *opr, t_fd *fd_node)
{
	while (opr)
	{
		fd_node = create_fd_node(fd_node);
		if (opr->token == OUT)
		{
			fd_node->file_fd = open(opr->path, O_RDWR | O_CREAT | O_TRUNC | O_CLOEXEC, 00644);
		}
		else if (opr->token == APP)
		{
			fd_node->file_fd = open(opr->path, O_RDWR | O_CREAT | O_APPEND | O_CLOEXEC, 00644);
		}
		else
		{
			if (access(opr->path, F_OK) == -1)
			{
				write(2, "Error: bad path file.\n", 22);
				info->status = 1;
				return (1);
			}
			fd_node->file_fd = open(opr->path, O_RDONLY);
		}
		fd_node->fd = opr->fd;
		fd_node->fd_clone = dup(opr->fd);
		dup2(fd_node->file_fd, fd_node->fd);
		opr = opr->next;
	}
	info->status = 0;
	return (0);
}
