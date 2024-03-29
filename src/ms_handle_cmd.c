/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_handle_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 07:02:15 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/07/17 11:10:53 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_formatted_env(char **env)
{
	__int32_t	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		env[i] = NULL;
		i++;
	}
	free(env);
	env = NULL;
}

static int	env_len(t_env *node)
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

static char	**format_env(t_info *info)
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

	env = format_env(info);
	pid = fork();
	if (pid == 0)
	{
		ms_init_pipe_child(node, info);
		info->subshl = 1;
		execve(cmd->cmd, cmd->args, env);
		info->status = 127;
		info->exit_status = info->status;
		write(2, "Error: command not found.\n", 27);
		ms_end_execution_child(info);
	}
	ms_end_execution(node->token, info, pid);
	free_formatted_env(env);
	return (info->status);
}

void	ms_handle_cmd(t_node *node, t_info *info)
{
	if (node->cmd == NULL)
	{
		return ;
	}
	if (ms_cmd_built_in(info, node) == -1)
	{
		ms_format_cmd(node->cmd, info);
		info->status = ms_execute_cmd(node, node->cmd, info);
		info->exit_status = info->status;
	}
}
