/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_tree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 11:15:31 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/29 11:47:08 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_fd	*create_fd_node(t_fd *node)
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

static int	handle_oprs(t_opr *opr, t_fd *fd_node)
{
	while (opr)
	{
		fd_node->fd = opr->fd;
		fd_node->fd_clone = dup(opr->fd);
		fd_node->file_fd = open(opr->arg, O_RDWR);
		if (fd_node->file_fd == -1)
		{
			write(2, "Error: bad path file.\n", 22);
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
	return (0);
}

static void	ms_restore_fd(t_fd *fd_lis)
{
	t_fd	*tmp;

	while (fd_lis)
	{
		if (fd_lis->file_fd != 0)
		{
			dup2(fd_lis->fd_clone, fd_lis->fd);
			close(fd_lis->fd_clone);
			close(fd_lis->file_fd);
		}
		tmp = fd_lis;
		fd_lis = fd_lis->next;
		free(tmp);
	}
}

int	ms_check_out(char token, int status, t_fd *fd_lis)
{
	if (token == OR && status == 1)
	{
		return (0);
	}
	else if (token != OR && status == 0)
	{
		return (0);
	}
	ms_restore_fd(fd_lis);
	return (-1);
}

void	ms_execute_tree(t_node *node, t_info *info)
{
	t_fd	*fd_lis;
	pid_t	pid;

	while (node)
	{
		fd_lis = create_fd_node(NULL);
		// ps_expander(node, info->env);
		// printf("cmd: |%s|\n", node->cmd->cmd);/////////////
		info->status = handle_oprs(node->opr, fd_lis);
		if (info->status == 0)
		{
			info->status = ms_handle_cmd(node, info, fd_lis);
		}
		if (ms_check_out(node->token, info->status, fd_lis) == -1)
		{
			return ;
		}
		if (node->subshl)
		{
			pid = fork();
			if (pid == 0)
			{
				ms_execute_tree(node->subshl, info);
				exit(info->status);
			}
			ms_waitpid(pid, info);
		}
		ms_restore_fd(fd_lis);
		node = node->next;
	}
}
