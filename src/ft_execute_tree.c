/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_tree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 11:15:31 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/22 11:29:41 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void handle_oprs(t_node *node, t_fd *fd_lis)
{
    t_opr   *opr;

    opr = node->opr;
    while (opr)
    {

        opr = opr->next;
    }
}

void    ft_execute_tree(t_node *node, t_info *info)
{
    // t_opr   *opr;
    t_fd    *fd_lis;

    while (node)
    {
        // opr = node->opr;
        // while (opr)
        // {
            
        //     opr = node->opr;
        // }

        /// ft_free_fd_lis(fd_lis); ///
        node = node->next;
    }
}
