/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 02:53:39 by sav               #+#    #+#             */
/*   Updated: 2023/05/17 15:46:34 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expansion(char *str, t_env *env)
{
	int	flag[2];
	int	i;

	flag[0] = 0;
	i = 0;
}

void	ps_expander(t_node *node, t_env *env)
{
	t_opr	*opr;
	size_t	i;

	node->cmd->cmd = expansion(node->cmd->cmd, env);
	i = 0;
	while (node->cmd->args[i])
	{
		node->cmd->args[i] = expansion(node->cmd->args[i], env);
		i++;
	}
	opr = node->opr;
	while (opr->next)
	{
		opr->arg = expansion(opr->arg, env);
		opr = opr->next;
	}
	opr->arg = expansion(opr->arg, env);
}
