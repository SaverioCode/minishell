/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sav <sav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:12:09 by sav               #+#    #+#             */
/*   Updated: 2023/07/17 06:43:25 by sav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_cmd(t_cmd *cmd)
{
	int	i;

	if (cmd->cmd)
	{
		free(cmd->cmd);
	}
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
	free(cmd);
}

static void	free_oprs(t_opr *opr)
{
	t_opr	*var;

	while (opr)
	{
		if (opr->path)
		{
			free(opr->path);
		}
		if (opr->arr)
		{
			ft_free_arr(opr->arr);
		}
		var = opr;
		opr = opr->next;
		free(var);
	}
}

static void	free_tnode(t_node *node)
{
	t_node	*var;

	while (node)
	{
		if (node->opr)
		{	
			free_oprs(node->opr);
		}
		if (node->cmd)
		{
			free_cmd(node->cmd);
		}
		if (node->subshl)
		{
			free_tnode(node->subshl);
		}
		var = node;
		node = node->next;
		free(var);
	}
}

void	ms_free(t_node *node, t_info *info)
{
	if (node)
	{
		free_tnode(node);
	}
	if (info)
	{
		ms_free_info(info);
	}
}
