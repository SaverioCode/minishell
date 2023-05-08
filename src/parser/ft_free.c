/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:12:09 by sav               #+#    #+#             */
/*   Updated: 2023/05/08 11:15:06 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	free(cmd);
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

static void	ft_free_nodes(t_node *node)
{
	t_node	*var;
	t_exp	*exp;

	while(node)
	{
		exp = node->exps;
		while (exp)
		{
			free(exp->exp);
			ft_free_oprs(exp->opr);
			ft_free_cmd(exp->cmd);
			exp = exp->next;
		}
		free(exp);
		var = node;
		node = node->next;
		free(var);
	}
}

void	ft_free(t_node *node, t_input *input)
{
	ft_free_node(node);
	free(input->starting);
	free(input->current);
}
