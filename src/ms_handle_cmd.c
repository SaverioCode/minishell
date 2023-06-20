/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_handle_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 07:02:15 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/06/21 00:39:17 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	built_in(t_cmd *cmd, t_info *info)
{
	if (ft_strncmp("cd", cmd->cmd, 2) == 1)
	{
		info->status = bi_cd(info, cmd->args);
	}
	else if (ft_strncmp("pwd", cmd->cmd, 3) == 1)
	{
		info->status = bi_pwd(cmd->args);
	}
	else
	{
		return (1);
	}
	return (0);
}

static int	ms_execute_cmd(t_node *node, t_cmd *cmd, t_info *info)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		ms_init_pipe_child(node, info);
		execve(cmd->cmd, cmd->args, info->env);
		info->status = 1;
		//// write command error ////
		write(2, "Error: command not found: \n", 27);
		ms_end_execution_child(node, info);
	}
	ms_end_execution(node->token, info, pid);
	return (info->status);
}

void	ms_handle_cmd(t_node *node, t_info *info)
{
	if (node->cmd == NULL)
	{
		return ;
	}
	if (built_in(node->cmd, info) == 1)
	{
		ms_format_cmd(node->cmd, info->env);
		info->status = ms_execute_cmd(node, node->cmd, info);
	}
}