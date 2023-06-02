/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:12:09 by sav               #+#    #+#             */
/*   Updated: 2023/06/01 20:19:26 by fgarzi-c         ###   ########.fr       */
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
	if (cmd)
	{
		free(cmd);
	}
}

static void	free_oprs(t_opr *opr)
{
	t_opr	*var;

	while (opr)
	{
		if (opr->arg)
		{
			free(opr->arg);
		}
		var = opr;
		opr = opr->next;
		free(var);
	}
}

static void	free_parse(t_node *node)
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
			free_parse(node->subshl);
		}
		var = node;
		node = node->next;
		free(var);
	}
}

static void	free_info(t_info *info)
{
	int		i;

	if (info->env)
	{
		i = 0;
		while (info->env[i])
		{
			free(info->env[i]);
			i++;
		}
		free(info->env);
	}
	if (info->input)
	{
		free(info->input);
	}
	if (info->prompt)
	{
		free(info->prompt);
	}
	close(info->stdin_clone);
	free(info);
}

void	ms_free(t_node *node, t_info *info)
{
	if (node)
	{
		free_parse(node);
	}
	if (info)
	{
		free_info(info);
	}
}
