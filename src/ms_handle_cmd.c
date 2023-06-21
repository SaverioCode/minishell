/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_handle_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 07:02:15 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/06/21 18:04:46 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	built_in(t_cmd *cmd, t_info *info)
{
	int	cmd_len;

	cmd_len = ft_strlen(cmd->cmd);
	if (ft_strncmp("cd", cmd->cmd, cmd_len) == 1)
	{
		info->status = bi_cd(info, cmd->args);
	}
	else if (ft_strncmp("exit", cmd->cmd, cmd_len) == 1)
	{
		info->status = bi_exit(info, cmd->args);
	}
	else if (ft_strncmp("pwd", cmd->cmd, cmd_len) == 1)
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

	/// get env formatted ///
	pid = fork();
	if (pid == 0)
	{
		ms_init_pipe_child(node, info);
		execve(cmd->cmd, cmd->args, NULL);
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
		ms_format_cmd(node->cmd, info);
		info->status = ms_execute_cmd(node, node->cmd, info);
	}
}