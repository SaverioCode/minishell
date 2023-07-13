/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmd_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 12:05:48 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/07/13 19:31:10 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_string(char *paths, char *cmd, int start, int end)
{
	char	*str;

	str = ft_getstr_from_to(paths, start, end);
	str = ft_strjoin(str, "/", 1, 0);
	str = ft_strjoin(str, cmd, 1, 0);
	return (str);
}

static int	check_acces(char *str, char *cmd, char *paths)
{
	if (access(str, X_OK) == 0)
	{
		free(cmd);
		free(paths);
		return (0);
	}
	return (-1);
}

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
			str = get_string(paths, cmd, start, i - 1);
			if (check_acces(str, cmd, paths) == 0)
				return (str);
			free(str);
			start = i + 1;
		}
		i++;
	}
	str = get_string(paths, cmd, start, i - 1);
	free(paths);
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
	}
	else
	{
		cmd->args = ft_push_str(ft_strcpy(cmd->cmd), cmd->args);
		cmd->cmd = get_cmd_path(info, cmd->cmd);
	}
}
