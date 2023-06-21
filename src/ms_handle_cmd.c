/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_handle_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 07:02:15 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/06/22 00:52:57 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	built_in(t_cmd *cmd, t_info *info)
{
	int	cmd_len;


/////// settare la pipe ////////////
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
	// else if (ft_strictcmp("export", cmd->cmd) == 0)
	// {
	// 	info->status = bi_export(info, cmd->args);
	// }
}

int	env_len(t_env *node)
{
	int	i;

	i = 0;
	while (node)
	{
		if (node->env == 1)
		{
			i++;
		}
		node = node->next;
	}
	return (i);
}

char	**format_env(t_info *info)
{
	char	**env;
	int		len;
	int		i;
	t_env	*node;

	if (info->env == NULL)
	{
		return (NULL);
	}
	len = env_len(info->env);
	env = ft_calloc(len + 1, 8);
	node = info->env;
	i = 0;
	while (i < len)
	{
		if (node->env == 1)
		{
			env[i] = ft_strjoin(node->name, "=", 0, 0);
			env[i] = ft_strjoin(env[i], node->value, 1, 0);
		}
		i++;
		node = node->next;
	}
	return (env);
}

static int	ms_execute_cmd(t_node *node, t_cmd *cmd, t_info *info)
{
	pid_t	pid;
	char	**env;
	/// get env formatted ///
	env = format_env(info);
	pid = fork();
	if (pid == 0)
	{
		ms_init_pipe_child(node, info);
		execve(cmd->cmd, cmd->args, env);
		info->status = 1;
		//// write command error ////
		write(2, "Error: command not found: \n", 27);
		ms_end_execution_child(node, info);
	}
	ms_end_execution(node->token, info, pid);
	free(env);
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