/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 23:15:57 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/08 13:35:26 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parser(t_node *root, t_info *info)
{
	t_node	*node;
	int		flag[2];

	if (!root || !info)
	{
		ft_free(root, info);
		// write error //
		exit(1);
	}
	flag[0] = 0;
	ft_separete_exps(root, info, flag);
	if (flag[0])
	{
		ft_free(node, info);
		write(2, "Error: quotes or parentesi\n", 27);
		exit(1);
	}
}
