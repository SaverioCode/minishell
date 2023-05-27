/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organize_exp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 06:57:18 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/27 12:51:29 by fgarzi-c         ###   ########.fr       */
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

static void	add_instruction(t_node *node, char *exp, int from, int *i)
{
	char	*str;
	t_opr	*opr;

	if (!exp)
	{
		return ;
	}
	str = ft_getstr_from_to(exp, from, *i - 1);
	if (exp[*i] == '<' || exp[*i] == '>')
	{
		opr = create_opr(node);
		if (ft_str_isdigit(str))
		{
			opr->fd = ft_atoi(str);
			free(str);
		}
		else
		{
			add_to_cmd(node, str);
			return ;
		}
		opr->token = lx_which_token(&exp[*i]);
		if (opr->token == HDOC || opr->token == APP)
			*i += 1;
		opr->arg = get_opr_arg(exp, i);
		return ;
	}
	add_to_cmd(node, str);
}

void	organize_exp(t_node *node, char *exp)
{
	int		from;
	int		i;
	int		flag[2];

	flag[0] = 0;
	from = 0;
	while (exp[from])
	{	
		if (ft_isprint(exp[from]))
			break ;
		from++;
	}
	i = from;
	while (exp[i])
	{
		lx_check_quotes(flag, exp[i]);
		if (!flag[0] && (!ft_isprint(exp[i]) || exp[i] == '<' || exp[i] == '>'))
		{
			if (from < i)
			{
				add_instruction(node, exp, from, &i);
			}
			from = i + 1;
		}
		i++;
	}
	exp = ft_trim(&exp[from], exp);
	i = ft_strlen(exp);
	add_instruction(node, exp, 0, &i);
	free(exp);
}
