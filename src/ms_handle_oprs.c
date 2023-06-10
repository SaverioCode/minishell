/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_handle_oprs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 20:52:41 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/06/10 01:01:16 by fgarzi-c         ###   ########.fr       */
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

int	here_document(t_opr *opr)
{
	char	buffer[2];
	char	*str;
	int		size;
	int		del_len;
	int		str_len;

	del_len = ft_strlen(opr->path);
	str = NULL;
	while (1)
	{
		size = read(opr->fd, buffer, 1);
		if (buffer[0] == '\n')
		{
			str_len = ft_strlen(str);
			if (del_len == str_len)
			{
				if (ft_strncmp(opr->path, str, ft_strlen(str)) == 1)
				{
					free(str);
					return (0);
				}
			}
			free(str);
			str = NULL;
			continue ;
		}
		str = ft_strjoin(str, buffer, 1, 0);
	}
	free(str);
}

int	input_redir(t_info *info, t_opr *opr, t_fd *fd_node)
{
	if (opr->token == HDOC)
	{
		if (here_document(opr) == 1)
		{
			return (1);
		}
	}
	else if (access(opr->path, F_OK) == -1)
	{
		write(2, "Error: bad path file.\n", 22);
		info->status = 1;
		return (1);
	}
	else if (opr->token == INP)
	{
		fd_node->file_fd = open(opr->path, O_RDONLY);
		if (fd_node->file_fd == -1)
		{
			return (1);
		}
		fd_node->fd = opr->fd;
		fd_node->fd_clone = dup(opr->fd);
		dup2(fd_node->file_fd, fd_node->fd);
	}
	return (0);
}

int	output_redir(t_opr *opr, t_fd *fd_node)
{
	if (opr->token == OUT)
	{
		fd_node->file_fd = open(opr->path, O_RDWR | O_CREAT | O_TRUNC | O_CLOEXEC, 00644);
	}
	else if (opr->token == APP)
	{
		fd_node->file_fd = open(opr->path, O_RDWR | O_CREAT | O_APPEND | O_CLOEXEC, 00644);
	}
	if (fd_node->file_fd == -1)
	{
		return (1);
	}
	fd_node->fd = opr->fd;
	fd_node->fd_clone = dup(opr->fd);
	dup2(fd_node->file_fd, fd_node->fd);
	return (0);
}

int	ms_handle_oprs(t_info *info, t_opr *opr, t_fd *fd_node)
{
	while (opr)
	{
		fd_node = create_fd_node(fd_node);
		if (opr->token == OUT || opr->token == APP)
		{
			if (output_redir(opr, fd_node) == 1)
			{
				return (1);
			}
		}
		else if (opr->token == INP || opr->token == HDOC)
		{
			if (input_redir(info, opr, fd_node) == 1)
			{
				return (1);
			}
		}
		opr = opr->next;
	}
	info->status = 0;
	return (0);
}
