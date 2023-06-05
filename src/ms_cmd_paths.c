/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmd_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 12:05:48 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/06/05 19:40:38 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_raw_paths(char **env)
{
	int	i;
	int	len;

	i = 0;
	while (env[i])
	{
		len = ft_strlen(env[i]);
		if (len >= 6)
		{
			if (ft_strncmp(env[i], "PATH=/", 6) == 1)
			{
				return (env[i]);
			}
		}
		i++;
	}
	return (NULL);
}

static char	*get_cmd_path(char **env, char *cmd)
{
	char	*paths;
	char	*str;
	int		i;
	int		start;

	paths = get_raw_paths(env);
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

static char	**add_cmd_to_args(char *cmd, char **args)
{
	char	**new;
	int		len;
	int		i;

	len = ft_biarrlen(args);
	if (!len)
	{
		new = ft_calloc(2, 8);
		new[0] = ft_strjoin(cmd, NULL, 0, 0);
		return (new);
	}
	new = ft_calloc(len + 2, 8);
	new[0] = ft_strjoin(cmd, NULL, 0, 0);
	i = 0;
	while (args[i])
	{
		new[1 + i] = args[i];
		i++;
	}
	free(args);
	return (new);
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

void	ms_format_cmd(t_cmd *cmd, char **env)
{
	if (access(cmd->cmd, X_OK) == 0)
	{
		cmd->args = add_cmd_to_args(get_cmd_from_path(cmd), cmd->args);
	}
	else
	{
		cmd->args = add_cmd_to_args(cmd->cmd, cmd->args);
		cmd->cmd = get_cmd_path(env, cmd->cmd);
	}
}
