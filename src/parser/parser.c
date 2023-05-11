/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 23:15:57 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/11 20:21:36 by fgarzi-c         ###   ########.fr       */
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
	/// check if last node is not empty and in case is empty and ///
	/// flag is set to END ask again for input ///
	/// maybe it could ft_separete_exps could be in a loop where ///
	/// this check occur and end only when conditions are satisfy ///
	if (flag[0])
	{
		write(2, "Error: quotes or parentesi\n", 27);
		return (-1);
	}
}
