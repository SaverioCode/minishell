/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_tree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 11:15:31 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/06/02 02:02:47 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ms_check_status(char token, int status)
{
	if (status == 1 && (token == OR || token == PIPE))
	{
		return (0);
	}
	else if (status == 0 && token != OR)
	{
		return (0);
	}
	// ms_restore_fd(fd_lis);
	return (1);
}

void	check_subshell(t_node *node, t_info *info)
{
	pid_t	pid;

	if (node->subshl)
	{
		pid = fork();
		if (pid == 0)
		{
			info->subshl = 1;
			ms_execute_tree(node->subshl, info);
			// clean memory //
			exit(info->status);
		}
		ms_waitpid(pid, info);
	}
}

void	ms_execute_tree(t_node *node, t_info *info)
{
	t_fd	*fd_lis;

	while (node)
	{
		fd_lis = create_fd_node(NULL);
		// ps_expander(node, info->env);
		if (ms_handle_oprs(info, node->opr, fd_lis) == 0)
		{
			/// maybe handle pipe here ///
			// init_pipe();
			ms_handle_cmd(node, info, fd_lis);
			// end_pipe();
		}
		if (ms_check_status(node->token, info->status) == 0)
		{
			check_subshell(node, info);
			ms_restore_fd(fd_lis);
			node = node->next;
		}
	}
	info->status = 0;
	// while (info->child->pid)
	// {
	// 	waitpid(info->child->pid, NULL, 0);
	// }
}
