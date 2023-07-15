/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_handle_oprs_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 19:44:14 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/07/15 22:07:53 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*here_doc_logic(t_opr *opr)
{
	char	*str;
	char	*buffer;

	buffer = NULL;
	str = NULL;
	while (1)
	{
		buffer = readline(">> ");
		rl_on_new_line();
		if (!buffer)
			continue ;
		if (ft_strictcmp(opr->path, buffer) == 0)
		{
			free(buffer);
			return (str);
			break ;
		}
		buffer = ft_strjoin(buffer, "\n", 1, 0);
		str = ft_strjoin(str, buffer, 1, 0);
		free(buffer);
		buffer = NULL;
	}
}

void	here_document(t_opr *opr, t_fd *fd_node)
{
	char	*str;
	int		fd[2];

	str = NULL;
	fd_node->fd = opr->fd;
	fd_node->fd_clone = dup(opr->fd);
	pipe(fd);
	str = here_doc_logic(opr);
	fd_node->file_fd = fd[0];
	write(fd[1], str, ft_strlen(str));
	dup2(fd[0], 0);
	close(fd[1]);
	close(fd[0]);
	free(str);
}

int	ms_input_redir(t_info *info, t_opr *opr, t_fd *fd_node)
{
	if (opr->token == HDOC)
	{
		here_document(opr, fd_node);
	}
	else if (access(opr->path, F_OK) == -1)
	{
		write(2, "Error: bad path file.\n", 22);
		info->status = 1;
		return (1);
	}
	else if (opr->token == INP)
	{
		fd_node->file_fd = open(opr->path, O_RDONLY | O_CLOEXEC, 00644);
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
