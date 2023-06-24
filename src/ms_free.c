/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sav <sav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:12:09 by sav               #+#    #+#             */
/*   Updated: 2023/06/24 09:30:23 by sav              ###   ########.fr       */
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

static void	free_env(t_env *node)
{
	t_env	*tmp;

	while (node)
	{
		free(node->name);
		free(node->value);
		tmp = node;
		node = node->next;
		free(tmp);
	}
}

static void	free_info(t_info *info)
{
	// clean child //
	// clean fd lis //
	if (info->env)
	{
		free_env(info->env);
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
	close(info->stdout_clone);
	free(info);
}

void	ms_free(t_node *node, t_info *info)
{
	if (node)
	{
		free_tnode(node);
	}
	if (info)
	{
		free_info(info);
	}
}
