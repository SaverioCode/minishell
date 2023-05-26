/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_tree_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 06:18:35 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/26 10:24:08 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_path   *create_new_node(t_path *node)
{
    t_path  *new;

    new = calloc(1, sizeof(t_path));
    new->str = NULL;
    new->next = NULL;
    if (node)
    {
        node->next = new;
    }
    return (new);
}

static size_t   lis_len(t_path *node)
{
    size_t  len;

    len = 0;
    if (!node)
    {
        return (len);
    }
    while (node->next)
    {
        len++;
        node = node->next;
    }
    return (len);
}

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

static void	get_cmd_paths(t_path *path, char **env, char *cmd)
{
	char	*paths;
	int		i;
	int		start;

	paths = get_raw_paths(env);
	if (!paths)
		return ;
	i = 5;
	start = i;
	while (paths[i])
	{
		if (!paths[i + 1])
		{
			path->str = ft_getstr_from_to(paths, start, i);
			path->str = ft_strjoin(path->str, "/", 1, 0);
			path->str = ft_strjoin(path->str, cmd, 1, 0);
		}
		if (paths[i] == ':')
		{
			path->str = ft_getstr_from_to(paths, start, i - 1);
			path->str = ft_strjoin(path->str, "/", 1, 0);
			path->str = ft_strjoin(path->str, cmd, 1, 0);
			path = create_new_node(path);
			start = i + 1;
		}
		i++;
	}
}

static char	**format_cmd_args(char *cmd, char **args)
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

void	ft_waitpid(int pid, t_info *info)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WSTOPSIG(status) == 1)
	{
		info->status = 1;
	}
	else if (WSTOPSIG(status) == 0)
	{
		info->status = 0;
	}
}

static int	execute_cmd(t_cmd *cmd, t_info *info, t_path *path, char token)
{
	pid_t	pid;
	int		paths_len;
	int		i;
	// int		fd[2];

	cmd->args = format_cmd_args(cmd->cmd, cmd->args);
	pid = fork();
	if (pid == 0)
	{
		paths_len = lis_len(path);
		i = 0;
		while (i < paths_len)
		{
			execve(path->str, cmd->args, info->env);
			path = path->next;
			i++;
		}
		write(2, "Error: occured in execve.\n", 26);
		exit(1);
	}
	ft_waitpid(pid, info);
	if (ft_check_out(token, info->status) == -1)
	{
		return (-1);
	}
	return (0);
}

static void	ft_free_path(t_path *path)
{
	t_path	*tmp;

	tmp = path;
	if (!path)
	{
		return ;
	}
	while (path)
	{
		tmp = path;
		path = path->next;
		free(tmp);
	}
}

int	ft_handle_cmd(t_node *node, t_info *info)
{
	t_path	*path;

	path = NULL;
	path = create_new_node(path);
	get_cmd_paths(path, info->env, node->cmd->cmd);
	if (execute_cmd(node->cmd, info, path, node->token) == -1)
	{
		ft_free_path(path);
		return (-1);
	}
	ft_free_path(path);
	return (0);
}