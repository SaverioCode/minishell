/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_tree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 11:15:31 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/27 17:33:51 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_fd	*create_fd_node(t_fd *node)
{
	t_fd	*fd_node;

	fd_node = ft_calloc(1, sizeof(fd_node));
	fd_node->std_fd = 0;
	fd_node->file_fd = 0;
	fd_node->next = NULL;
	if (node)
	{
		node->next = fd_node;
	}
	return (fd_node);
}

static int	handle_oprs(t_opr *opr, t_fd *fd_node)
{
	while (opr)
	{
		fd_node->std_fd = dup(opr->fd);
		fd_node->file_fd = open(opr->arg, O_RDWR);
		if (fd_node->file_fd == -1)
		{
			write(2, "Error: bad path file.\n", 22);
			return (1);
		}
		dup2(fd_node->file_fd, fd_node->std_fd);
		opr = opr->next;
		if (!opr)
		{
			break ;
		}
		fd_node = create_fd_node(fd_node);
	}
	return (0);
}

static int	check_fd_lis(t_fd *fd_lis)
{
	while (fd_lis)
	{
		if (fd_lis->std_fd == 1)
		{
			return (1);
		}
		fd_lis = fd_lis->next;
	}
	return (0);
}

int	ft_check_out(char token , int status)
{
	if (token == OR && status == 1)
	{
		return (0);
	}
	if ((token == AND || token == PIPE) && status == 0)
	{
		return (0);
	}
	return (-1);
}

void	ft_execute_tree(t_node *node, t_info *info)
{
	t_fd	*fd_lis;
	pid_t	pid;
	int		status_opr;
	int		status_cmd;

	fd_lis = create_fd_node(NULL);
	while (node)
	{
		// ps_expander(node, info->env);
		status_opr = handle_oprs(node->opr, fd_lis);
		status_cmd = ms_handle_cmd(node, info, fd_lis);
		/// se uno dei due e' negativo status va settato negativo ///
		if (ft_check_out(node->token, info->status) == -1)
		{
			return ;
		}
		if (node->subshl)
		{
			// write(1, "CHECK0\n", 7);//////////
			pid = fork();
			if (pid == 0)
			{
				ft_execute_tree(node->subshl, info);
				exit(info->status);
			}
			ft_waitpid(pid, info);
		}
		/// ft_free_fd_lis(fd_lis); ///
		ms_restore_fd(fd_lis);
		/// eventualy reset file descriptor ///

		node = node->next;
	}
}
