/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:12:09 by sav               #+#    #+#             */
/*   Updated: 2023/05/22 10:17:03 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free_cmd(t_cmd *cmd)
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

static void	ft_free_oprs(t_opr *opr)
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

static void	ft_free_parse(t_node *node)
{
	t_node	*var;

	while (node)
	{
		if (node->opr)
		{	
			ft_free_oprs(node->opr);
		}
		if (node->cmd)
		{	
			ft_free_cmd(node->cmd);
		}
		if (node->subshl)
		{
			ft_free_parse(node->subshl);
		}
		var = node;
		node = node->next;
		free(var);
	}
}

static void	ft_free_info(t_info *info)
{
	t_env	*env;
	t_env	*var;

	env = info->env;
	while (env)
	{
		if (env->name)
		{
			free(env->name);
		}
		if (env->value)
		{
			free(env->value);
		}
		var = env;
		env = env->next;
		free(env);
	}
	free(info);
}

void	ft_free(t_node *node, t_info *info)
{
	if (node)
	{
		ft_free_parse(node);
	}
	if (info)
	{
		ft_free_info(info);
	}
}
