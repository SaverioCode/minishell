/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:12:09 by sav               #+#    #+#             */
/*   Updated: 2023/05/19 21:23:46 by fgarzi-c         ###   ########.fr       */
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
			write(1, "1\n", 2);///
			ft_free_oprs(node->opr);
		}
		if (node->cmd)
		{	
			write(1, "2\n", 2);///
			ft_free_cmd(node->cmd);
		}
		if (node->subshl)
		{
			write(1, "3\n", 2);///
			ft_free_parse(node->subshl);
		}
		var = node;
		node = node->next;
		write(1, "ciao\n", 5);///
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
		write(1, "ciao1\n", 6);///
		ft_free_parse(node);
	}
	if (info)
	{
		write(1, "ciao2\n", 6);///
		ft_free_info(info);
	}
}
