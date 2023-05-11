/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 23:15:57 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/12 00:10:09 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parser(t_node *root, t_info *info)
{
	// t_node		*node;
	int			flag[2];
	static int	brackets;

	if (!root || !info)
	{
		ft_free(root, info);
		// write error //
		return (-1);
	}
	flag[0] = 0;
	if (ft_create_nodes(root, info, flag, &brackets) == -1)
		return (-1);
	/// if (flag[0]) I need to ask again for input ///
	/// se ft_create_nodes return 2 wait it means that the ///
	/// input is valid but end with OR, AND, or PIPE and then ///
	/// I need to ask again for input ///
}
