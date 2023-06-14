/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_handle_oprs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 20:52:41 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/06/14 22:15:21 by fgarzi-c         ###   ########.fr       */
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

int	here_document(t_opr *opr, t_fd *fd_node)
{
	char	*buffer;
	char	*str;
	int		del_len;
	int		str_len;

	del_len = ft_strlen(opr->path);
	str = NULL;
	buffer = NULL;
	fd_node->fd = opr->fd;
	fd_node->fd_clone = dup(opr->fd);
	int	fd[2];
	pipe(fd);
	while (1)
	{
		buffer = readline(">> ");
		rl_on_new_line();
		if (!buffer)
		{
			continue ;
		}
		str_len = ft_strlen(buffer);
		if (del_len == str_len)
		{
			if (ft_strncmp(opr->path, buffer, ft_strlen(buffer)) == 1)
			{
				free(buffer);
				break ;
			}
			free(buffer);
			buffer = NULL;
			continue ;
		}
		buffer = ft_strjoin(buffer, "\n", 1, 0);
		str = ft_strjoin(str, buffer, 1, 0);
		free(buffer);
		buffer = NULL;
	}
	fd_node->file_fd = fd[0];
	write(fd[1], str, ft_strlen(str));
	dup2(fd[0], 0);
	close(fd[1]);
	free(str);
	return (0);
}

int	input_redir(t_info *info, t_opr *opr, t_fd *fd_node)
{
	if (opr->token == HDOC)
	{
		if (here_document(opr, fd_node) == 1)
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
		fd_node = create_fd_node(get_fd_node(info->fd_lis, NULL));
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
