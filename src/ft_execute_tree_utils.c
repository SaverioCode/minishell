/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_tree_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 06:18:35 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/24 07:58:09 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.c"

static char *get_raw_paths(char **env)
{
    int i;
    int len;

    i = 0;
    while (env[i])
    {
        len = ft_strlen(env[i]);
        if (len >= 6)
        {
            if (ft_strncmp(env[i], "PATH=/", 6) == 0)
            {
                return (env[i]);
            }
        }
        i++;
    }
    return (NULL);
}

static void take_cmd_path(char **env, t_path *path, char *cmd)
{
    char    *paths;
    int     i;
    int     start;

    paths = get_raw_paths(env);
    if (!paths)
        return ;
    i = 5;
    start = i;
    while (paths[i])
    {
        if (!paths[i + 1])
        {
            path->str = ft_get_str(paths, start, i);
            path->str = ft_strjoin(path->str, cmd, 1, 0);
        }
        if (paths[i] == ':')
        {
            path->str = ft_getstr_from_to(paths, start, i - 1);
            path->str = ft_strjoin(path->str, cmd, 1, 0);
            path = create_new_node(path);
            start = i + 1;
        }
        i++;
    }
}

static char **format_cmd_args(char *cmd, char **args)
{
    char    **new;
    int     len;
    int     i;

    len = ft_biarrlen(args);
    new = ft_calloc(1, len + 1);
    args[0] = cmd;
    i = 0;
    while (args[i])
    {
        new[1 + i] = args[i];
        i++;
    }
    free(args);
    return (args);
}

static void ft_waitpid(int pid)
{
    int     $question_mark;
    int     status;

    waitpid(pid, &status, 0);
    if (WSTOPSIG(status) > 0)
    {
        $question_mark = 1;
    }
    else if (WSTOPSIG(status) == 0)
    {
        $question_mark = 0;
    }
}

static int  check_out(char *token , int status)
{

}

static void execute_cmd(t_cmd *cmd, char **args, char **env, char token)
{
    pid_t   pid;
    t_path  *paths;
    t_path  *path;
    int     num_of_paths;
    int     i;
    int     fd[2];

    args = format_cmd_args(cmd->cmd, args);
    get_cmd_paths(paths);
    if (token == PIPE && !check_fd_lis(fd_lis));
    {
        pipe(fd);
    }
    pid = fork();
    if (pid == 0)
    {
        path = paths;
        num_of_paths = lis_len(paths);
        i = 0;
        while (i < num_of_paths)
        {
            execve(path->str, args, env);
            path = path->next;
            i++;
        }
        write(2, "Error: occured in execve.\n", 26);
        exit(0);
    }
    ft_waitpid(pid);
}
