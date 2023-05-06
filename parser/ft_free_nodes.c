/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_nodes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sav <sav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:12:09 by sav               #+#    #+#             */
/*   Updated: 2023/05/06 18:27:21 by sav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	ft_free_cmd(t_cmd *cmd)
{
	int	i;

	free(cmd->cmd);
	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
		{
			free(cmd->args[i]);
			i++;
		}
		free(cmd->args);
	}
}

static void	ft_free_oprs(t_opr *opr)
{
	t_opr	*var;

	while (opr)
	{
		free(opr->fd);
		free(opr->arg);
		var = opr;
		opr = opr->next;
		free(var);
	}
}

void	ft_free_nodes(t_node *node)
{
	t_node	*var;

	while(node)
	{
		free(node->exp);
		ft_free_oprs(node->opr);
		free(node->opr);
		free_cmd(node->cmd);
		free(node->cmd);
		var = node;
		node = node->next;
		free(var);
	}
}
