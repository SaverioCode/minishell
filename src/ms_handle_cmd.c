/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_handle_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 07:02:15 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/06/21 19:08:49 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	built_in(t_cmd *cmd, t_info *info)
{
	int	cmd_len;

	cmd_len = ft_strlen(cmd->cmd);
	if (ft_strictcmp("cd", cmd->cmd) == 0)
	{
		info->status = bi_cd(info, cmd->args);
	}
	else if (ft_strictcmp("exit", cmd->cmd) == 0)
	{
		info->status = bi_exit(info, cmd->args);
	}
	else if (ft_strictcmp("pwd", cmd->cmd) == 0)
	{
		info->status = bi_pwd(cmd->args);
	}
	else if (ft_strictcmp("env", cmd->cmd) == 0)
	{
		info->status = bi_env(info->env, cmd->args);
	}
	else if (ft_strictcmp("unset", cmd->cmd) == 0)
	{
		info->status = bi_unset(info, cmd->args);
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