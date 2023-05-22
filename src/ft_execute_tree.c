/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_tree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 11:15:31 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/22 13:26:46 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_fd *create_fd_node(t_fd *node)
{
    t_fd    *fd_node;

    fd_node = ft_calloc(1, sizeof(fd_node));
    fd_node->std_fd = 0;
    fd_node->file_fd = 0;
    fd_node->next = NULL;
    if (node)
    {
        node->next = fd_node;
    }
    return (fd_node);
}

static int  handle_oprs(t_opr *opr, t_fd *fd_node)
{
    while (opr)
    {
        fd_node->std_fd = opr->fd;
        fd_node->file_fd = open(opr->arg, O_RDWR);
        if (fd_node->file_fd == -1)
        {
            write(2, "Error: bad path file.\n", 22);
            return (-1);
        }
        dup2(fd_node->file_fd, fd_node->std_fd);
        opr = opr->next;
        if (!opr)
        {
            break ;
        }
        fd_node = create_fd_node(fd_node);
    }
}

static int  handle_cmd(t_cmd *cmd, char token, char **env)
{
    pid_t   pid;

    pid = fork();
    if (pid != 0)
    {
        if (execve("", "", env) == -1)
        {
            write(2, "Error: command or arguments are invalid.\n", 41);
            return (-1);
        }
    }
}

void    ft_execute_tree(t_node *node, t_info *info)
{
    t_fd    *fd_lis;

    fd_lis = create_fd_node(NULL);
    while (node)
    {
        if (handle_oprs(node->opr, fd_lis) == -1)
        {
            /// ft_free_fd_lis(fd_lis); ///
            return ;
        }
        if (handle_cmd(node->cmd, node->token, info->env) == -1)
        {
            /// set $? = 1; ///
        }
        if (node->subshl)
        {
            ft_execute_tree(node->subshl, info);
        }
        /// ft_free_fd_lis(fd_lis); ///
        node = node->next;
    }
}
