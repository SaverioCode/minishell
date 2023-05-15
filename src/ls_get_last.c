/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_get_last.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 23:15:57 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/15 11:38:33 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*ls_get_last_tnode(t_node *node, char c)
{
	if (!node)
		return (0);
	if (c = 'n')
	{
		while (node->next)
			node = node->next;
		return (node);
	}
	else if (c = 's')
	{
		while (node->subshl)
			node = node->subshl;
		return (node);
	}

}
