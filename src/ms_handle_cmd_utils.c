/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_handle_cmd_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sav <sav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 02:15:52 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/07/10 18:31:47 by sav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	built_in_1_5(t_info *info, t_cmd *cmd, bi_cmd token)
{
	if (token == BI_CD)
	{
		info->status = bi_cd(info, cmd->args);
	}
	else if (token == BI_ECHO)
	{
		info->status = bi_echo(cmd->args);
	}
	else if (token == BI_ENV)
	{
		info->status = bi_env(info->env, cmd->args);
	}
	else if (token == BI_EXIT)
	{
		info->status = bi_exit(info, cmd->args);
	}
	else if (token == BI_EXPORT)
	{
		info->status = bi_export(info, cmd->args);
	}
}

static void	built_in_6_10(t_info *info, t_cmd *cmd, bi_cmd token)
{
	if (token == BI_PWD)
	{
		info->status = bi_pwd(cmd->args);
	}
	else if (token == BI_UNSET)
	{
		info->status = bi_unset(info, cmd->args);
	}
}

static int	is_built_in(char *cmd)
{
	if (ft_strictcmp("cd", cmd) == 0)
		return(BI_CD);
	if (ft_strictcmp("echo", cmd) == 0)
		return(BI_ECHO);
	if (ft_strictcmp("env", cmd) == 0)
		return(BI_ENV);
	if (ft_strictcmp("exit", cmd) == 0)
		return(BI_EXIT);
	if (ft_strictcmp("export", cmd) == 0)
		return(BI_EXPORT);
	if (ft_strictcmp("pwd", cmd) == 0)
		return(BI_PWD);
	if (ft_strictcmp("unset", cmd) == 0)
		return(BI_UNSET);
	return (BI_NULL);
}

static void	execute_built_in(t_info *info, t_node *node, bi_cmd token)
{
	if (node->token == PIPE)
	{
		if (ms_check_fd_lis(info->fd_lis, 1) == -1)
		{
			close(info->fd[1]);
			return ;
		}
		dup2(info->fd[1], 1);
	}
	if (token < 6)
	{
		built_in_1_5(info, node->cmd, token);
	}
	else if (token > 5 && token < 11)
	{
		built_in_6_10(info, node->cmd, token);
	}
	if (info->pipe == 1)
	{
		close(info->fd[1]);
		dup2(info->stdout_clone, 1);
	}
}

int	ms_cmd_built_in(t_info *info, t_node *node)
{
	bi_cmd	token;

	token = is_built_in(node->cmd->cmd);
	if (token == 0)
	{
		return (-1);
	}
	execute_built_in(info, node, token);
	return (0);
}
