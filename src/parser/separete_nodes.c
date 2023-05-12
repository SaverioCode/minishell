/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separete_nodes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 23:15:57 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/12 06:54:57 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_token_and_exp(t_node *node, t_info *info, int i)
{
	int	status;

	if (get_token(node, info, i) == -1)
		return (-1);
	cut_exp(node, info, i);
	cut_token(node, info);
	update_current_input(node, info);
	status = check_exp(node);
	return (status);
}
