/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_handle_oprs_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sav <sav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 19:44:14 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/07/17 07:03:34 by sav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_here_doc(t_info *info, t_opr *opr, t_fd *fd_node)
{
	__int32_t	fd[2];
	__int32_t	i;

	fd_node->fd = opr->fd;
	fd_node->fd_clone = dup(opr->fd);
	pipe(fd);
	i = 0;
	while (opr->arr && opr->arr[i])
	{
		opr->arr[i] = ps_expand(opr->arr[i], info);
		write(fd[1], opr->arr[i], ft_strlen(opr->arr[i]));
		free(opr->arr[i]);
		i++;
	}
	free(opr->arr);
	opr->arr = NULL;
	fd_node->file_fd = fd[0];
	if (opr->fd == 0 && info->pipe == 1)
	{
		close(info->fd[0]);
		dup2(info->stdin_clone, 0);
	}
	close(fd[1]);
	dup2(fd[0], opr->fd);
	close(fd[0]);
}

void	here_document(t_opr *opr)
{
	char	*buffer;

	buffer = NULL;
	while (1)
	{
		buffer = readline(">> ");
		rl_on_new_line();
		if (!buffer)
			continue ;
		if (ft_strictcmp(opr->path, buffer) == 0)
		{
			free(buffer);
			return ;
		}
		buffer = ft_strjoin(buffer, "\n", 1, 0);
		opr->arr = ft_append_str(opr->arr, buffer);
		buffer = NULL;
	}
}

int	ms_input_redir(t_info *info, t_opr *opr, t_fd *fd_node)
{
	if (opr->token == HDOC)
	{
		dup_here_doc(info, opr, fd_node);
	}
	else if (access(opr->path, F_OK) == -1)
	{
		write(2, "Error: bad path file.\n", 22);
		info->status = 1;
		info->exit_status = info->status;
		return (1);
	}
	else if (opr->token == INP)
	{
		if (opr->fd == 0 && info->pipe == 1)
			dup2(info->stdin_clone, 0);
		fd_node->file_fd = open(opr->path, O_RDONLY | O_CLOEXEC, 00644);
		if (fd_node->file_fd == -1)
		{
			info->status = 1;
			info->exit_status = info->status;
			return (1);
		}
		fd_node->fd = opr->fd;
		fd_node->fd_clone = dup(opr->fd);
		dup2(fd_node->file_fd, fd_node->fd);
	}
	return (0);
}

void	ms_handle_here_doc(t_node *node)
{
	t_opr	*opr;

	while (node)
	{
		opr = node->opr;
		while (opr)
		{
			if (opr->token == HDOC)
			{
				here_document(opr);
			}
			opr = opr->next;
		}
		if (node->subshl)
		{
			ms_handle_here_doc(node->subshl);
		}
		node = node->next;
	}
}

int	ms_output_redir(t_opr *opr, t_fd *fd_node)
{
	if (opr->token == OUT)
	{
		fd_node->file_fd = open(opr->path, \
			O_RDWR | O_CREAT | O_TRUNC | O_CLOEXEC, 00644);
	}
	else if (opr->token == APP)
	{
		fd_node->file_fd = open(opr->path, \
			O_RDWR | O_CREAT | O_APPEND | O_CLOEXEC, 00644);
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
