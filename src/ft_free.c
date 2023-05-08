/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:12:09 by sav               #+#    #+#             */
/*   Updated: 2023/05/08 13:04:05 by fgarzi-c         ###   ########.fr       */
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

void	ft_free_parse(t_node *node)
{
	t_node	*var;
	t_exp	*exp;
	t_exp	*old_exp;

	while(node)
	{
		exp = node->exps;
		while (exp)
		{
			free(exp->exp);
			ft_free_oprs(exp->opr);
			ft_free_cmd(exp->cmd);
			old_exp = exp;
			exp = exp->next;
			free(exp);
		}
		var = node;
		node = node->next;
		free(var);
	}
}

void	ft_free_info(t_info *info)
{
	t_env	*env;
	t_env	*var;

	env = info->env;
	while (env)
	{
		free(env->name);
		free(env->value);
		var = env;
		env = env->next;
		free(env);		
	}
	free(info);
}

void	ft_free(t_node *node, t_info *info)
{
	ft_free_parse(node);
	ft_free_info(info);
}
