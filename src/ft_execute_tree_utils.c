/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_tree_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 06:18:35 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/27 17:55:28 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ms_execute_cmd(t_cmd *cmd, t_info *info, t_path *path)
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
	return (0);
}
