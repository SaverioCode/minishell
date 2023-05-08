/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 10:35:21 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/08 13:30:04 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_tcmd(t_cmd *node)
{
	node->cmd = NULL;
	node->args = NULL;
}

void	set_topr(t_opr *node)
{
	node->fd = NULL;
	node->arg = NULL;
	node->next = NULL;
}

void	set_texp(t_exp *node)
{
	node->shlvl = 0;
	node->token = NULL;
	node->status = 0;
	node->exp = NULL;
	node->cmd = NULL;
	node->opr = NULL;
	node->next = NULL;
}

void	set_tnode(t_node *node)
{
	node->token = 0;
	node->status = 0;
	node->fd_output = 0;
	node->exps = NULL;
	node->next = NULL;
}
