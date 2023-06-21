/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmd_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 12:05:48 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/06/21 18:00:45 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_cmd_path(t_info *info, char *cmd)
{
	char	*paths;
	char	*str;
	int		i;
	int		start;

	paths = ms_get_env_value(info, "PATH");
	if (!paths)
		return (NULL);
	i = 5;
	start = i;
	while (paths[i])
	{
		if (paths[i] == ':')
		{
			str = ft_getstr_from_to(paths, start, i - 1);
			str = ft_strjoin(str, "/", 1, 0);
			str = ft_strjoin(str, cmd, 1, 0);
			if (access(str, X_OK) == 0)
			{
				free(cmd);
				return (str);
			}
			else
			{
				free(str);
			}
			start = i + 1;
		}
		i++;
	}
	str = ft_getstr_from_to(paths, start, i - 1);
	str = ft_strjoin(str, "/", 1, 0);
	str = ft_strjoin(str, cmd, 1, 0);
	free(cmd);
	return (str);
}

static char	*get_cmd_from_path(t_cmd *cmd)
{
	char	*command;
	int		len;
	int		i;

	len = ft_strlen(cmd->cmd);
	i = len;
	while (i >= 0)
	{
		if (cmd->cmd[i] == '/')
		{
			break ;
		}
		i--;
	}
	if (i < 0)
	{
		return (NULL);
	}
	command = ft_getstr_from_to(cmd->cmd, i + 1, len);
	return (command);
}

void	ms_format_cmd(t_cmd *cmd, t_info *info)
{
	char	*cmd_without_path;

	if (access(cmd->cmd, X_OK) == 0)
	{
		cmd_without_path = get_cmd_from_path(cmd);
		cmd->args = ft_push_str(cmd_without_path, cmd->args);
		free(cmd_without_path);
	}
	else
	{
		cmd->args = ft_push_str(cmd->cmd, cmd->args);
		cmd->cmd = get_cmd_path(info, cmd->cmd);
	}
}
