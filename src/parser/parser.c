/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 23:15:57 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/09 19:52:17 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parser(t_node *root, t_info *info)
{
	t_node	*node;
	int		flag[2];

	if (!root || !info)
	{
		ft_free(root, info);
		// write error //
		return (-1);
	}
	flag[0] = 0;
	if (ft_separete_exps(root, info, flag) == -1)
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
