/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execution_utils_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:37:54 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/07/15 23:21:53 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_waitpid(pid_t pid, t_info *info)
{
	int	status;

	waitpid(pid, &status, 0);
	info->status = WSTOPSIG(status);
	info->exit_status = info->status;
}

void	ms_store_pid(t_info *info, pid_t pid)
{
	t_child	*new;
	t_child	*child;

	new = ft_calloc(1, sizeof(t_child));
	new->pid = 0;
	new->pid = pid;
	new->next = NULL;
	if (info->child == NULL)
	{
		info->child = new;
		return ;
	}
	child = info->child;
	while (child->next)
	{
		child = child->next;
	}
	child->next = new;
}

void	ms_waitchild(t_info *info)
{
	t_child	*child;
	t_child	*tmp;

	child = info->child;
	while (child)
	{
		ms_waitpid(child->pid, info);
		tmp = child;
		child = child->next;
		free(tmp);
	}
	info->child = NULL;
}
