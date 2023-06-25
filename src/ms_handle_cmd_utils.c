/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_handle_cmd_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sav <sav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 02:15:52 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/06/25 21:10:37 by sav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void	built_in_1_6(t_info *info, t_cmd *cmd, bi_cmd token)
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
	else if (token == BI_PWD)
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
	if (ft_strictcmp("cd", cmd) == 0 || ft_strictcmp("CD", cmd) == 0)
	{
		return(BI_CD);
	}
	else if (ft_strictcmp("echo", cmd) == 0 || ft_strictcmp("ECHO", cmd) == 0)
	{
		return(BI_ECHO);
	}
	else if (ft_strictcmp("exit", cmd) == 0 || ft_strictcmp("EXIT", cmd) == 0)
	{
		return(BI_EXIT);
	}
	else if (ft_strictcmp("pwd", cmd) == 0 || ft_strictcmp("PWD", cmd) == 0)
	{
		return(BI_PWD);
	}
	else if (ft_strictcmp("env", cmd) == 0 || ft_strictcmp("ENV", cmd) == 0)
	{
		return(BI_ENV);
	}
	else if (ft_strictcmp("unset", cmd) == 0 || ft_strictcmp("UNSET", cmd) == 0)
	{
		return(BI_UNSET);
	}
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
	if (token < 7)
	{
		built_in_1_6(info, node->cmd, token);
	}
	// else if (bi_token > 4 && bi_token < 10)
	// {
	// 	built_in_0_10(info, node);
	// }
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
