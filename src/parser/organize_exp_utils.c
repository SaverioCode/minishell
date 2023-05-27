/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organize_exp_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 14:34:09 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/27 14:47:28 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_opr	*create_opr(t_node *node)
{
	t_opr	*opr;
	t_opr	*old;

	opr = ft_calloc(1, sizeof(t_opr));
	init_topr(opr);
	if (!node->opr)
	{	
		node->opr = opr;
		return (opr);
	}
	old = node->opr;
	while (old->next)
	{
		old = old->next;
	}
	old->next = opr;
	return (opr);
}

static void	add_to_cmd(t_node *node, char *str)
{
	char	**new;
	int		i;

	if (!node->cmd)
	{
		node->cmd = ft_calloc(8, 1);
		init_tcmd(node->cmd);
		node->cmd->cmd = str;
		return ;
	}
	if (!node->cmd->args)
	{
		node->cmd->args = ft_calloc(8, 2);
		node->cmd->args[0] = str;
		return ;
	}
	i = ft_biarrlen(node->cmd->args);
	new = ft_calloc(i + 2, 8);
	new[i] = str;
	i--;
	while (i >= 0)
	{
		new[i] = node->cmd->args[i];
		i--;
	}
	free(node->cmd->args);
	node->cmd->args = new;
}

static char	*get_opr_arg(char *exp, int *i)
{
	char	*arg;
	int		j;

	*i += ft_find_printable(&exp[*i + 1], '+') + 1;
	j = *i;
	while (exp[j])
	{
		if (!ft_isprint(exp[j]))
		{
			break ;
		}
		j++;
	}
	arg = ft_getstr_from_to(exp, *i, j - 1);
	*i = j - 1;
	return (arg);
}

static int	get_opr_exp(t_node *node, char *fd, char *exp, int *i)
{
	t_opr	*opr;

	opr = create_opr(node);
	opr->token = lx_which_token(&exp[*i]);
	if (opr->token == HDOC || opr->token == APP)
	{
		*i += 1;
	}
	opr->arg = get_opr_arg(exp, i);
	if (ft_str_isdigit(fd))
	{
		opr->fd = ft_atoi(fd);
		free(fd);
		return (0);
	}
	if (opr->token == INP || opr->token == HDOC)
	{
		opr->fd = 0;
	}
	else if (opr->token == OUT || opr->token == APP)
	{
		opr->fd = 1;
	}
	return (-1);
}

void	ps_add_instruction(t_node *node, char *exp, int from, int *i)
{
	char	*str;

	if (!exp)
	{
		return ;
	}
	str = ft_getstr_from_to(exp, from, *i - 1);
	if (exp[*i] == '<' || exp[*i] == '>')
	{
		if (get_opr_exp(node, str, exp, i) == 0)
		{
			return ;
		}
		if (ft_find_printable(str, '+') == -1)
		{
			free(str);
			return ;
		}
	}
	add_to_cmd(node, str);
}
