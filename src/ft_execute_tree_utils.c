/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_tree_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 06:18:35 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/26 08:46:56 by fgarzi-c         ###   ########.fr       */
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
	path = create_new_node(path);
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
	new = ft_calloc(len + 1, 8);
	new[0] = ft_strjoin(cmd, NULL, 0, 0);
	i = 0;
	while (args[i])
	{
		new[1 + i] = args[i];
		printf("|%s|\n", new[i + 1]);//////////
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

int	handle_cmd(t_cmd *cmd, t_info *info, char token)
{
	pid_t	pid;
	t_path	*path;
	int		paths_len;
	int		i;
	// int		fd[2];

	write(1, "CMD1\n", 5);///////////
	cmd->args = format_cmd_args(cmd->cmd, cmd->args);
	write(1, "CMD2\n", 5);///////////
	path = NULL;
	get_cmd_paths(path, info->env, cmd->cmd);
	write(1, "CMD3\n", 5);///////////
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
