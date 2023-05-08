/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 23:15:57 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/08 12:38:25 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parser(t_node *root, t_info *info)
{
	t_node	*node;

	if (!root)
	{
		ft_free(NULL, info);
		// write error //
		exit(1);
	}
	ft_separete_exps(root, info);
	node = root;
	while (node)
	{
		ft_create_exps_tree(root);
		node = node->next;
	}
}
