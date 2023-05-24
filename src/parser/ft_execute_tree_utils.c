/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_tree_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 04:19:27 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/24 04:29:58 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char **format_args(char *cmd, char **args)
{
    char    **new;
    int     len;
    int     i;

    len = ft_biarrlen(args);
    new = ft_calloc(args + 1, 8);
    args[0] = cmd;
    i = 0;
    while (args[i])
    {
        args[i + 1] = args[i];
        i++;
    }
    free(args);
}

static void execute_cmd(t_cmd *cmd, char token, char **args, t_info *info)
{
    pid_t    pid;
    t_paths  *path;
    int     num_of_paths;
    int     i;

    args = format_args(cmd->cmd, args);
    pid = fork();
    if (pid == 0)
    {
        path = paths;
        num_of_paths = lis_len(paths);
        i = 0;
        while (i < num_of_paths)
        {
            execve(path->path, args, env);
            path = path->next;
            i++;
        }
        write(2, "Error: occured in execve.\n", 26);
        exit(0);
    }
    ft_waitpid(pid);
}

static int  handle_cmd(t_cmd *cmd, char token, t_info *info)
{
    pid_t   pid;

    pid = fork();
    if (pid != 0)
    {
        if (execve("", "", info->env) == -1)
        {
            write(2, "Error: command or arguments are invalid.\n", 41);
            info->status = 1;
            if (token == AND)
            {
                return (-1);
            }
        }
    }
    else
    {
        wait(NULL);
    }
}
