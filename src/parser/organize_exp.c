/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organize_exp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 06:57:18 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/17 03:14:12 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_opr	*create_sopr(t_node *node)
{
	t_opr	*opr;
	t_opr	*old;

	opr = ft_calloc(8, 1);
	init_topr(opr);
	if (!node->opr)
	{	
		node->opr = opr;
	}
	old = node->opr;
	while (old->next)
	{
		old = old->next;
	}
	old->next = opr;
	return (opr);
}

static t_opr	*get_rigth_opr(t_node *node)
{
	t_opr	*opr;

	if (!node->opr)
	{
		opr = ft_calloc(8, 1);
		init_topr(opr);
		node->opr = opr;
		return (opr);
	}
	opr = node->opr;
	while (opr->next)
	{
		opr = opr->next;
	}
	if (!opr->arg)
	{	
		return (opr);
	}
	opr->next = ft_calloc(8, 1);
	init_topr(opr->next);
	return (opr->next);
}

static void	add_instruction(t_node *node, char *exp, int from, int *i)
{
	char	*str;
	t_opr	*opr;

	str = ft_getstr_from_to(exp, from, *i);
	if (exp[*i] == '<' || exp[*i] == '>')
	{
		opr = get_rigth_opr(node);
		if (ft_str_isdigit(str))
		{
			opr->fd = ft_atoi(str);
			free(str);
		}
		else
		{
			// function //
		}
		opr->token = lx_which_token(&exp[*i]);
	}
	else if ()
	{
		opr = get_rigth_opr(node);

		// function //
	}
}

void	organize_exp(t_node *node)
{
	char	*str;
	int		from;
	int		i;
	int		flag[2];

	flag[0] = 0;
	from = 0;
	while (node->exp[from])
	{	
		if (ft_isprint(node->exp[from]))
			break ;
		from++;
	}
	i = from;
	while (node->exp[i])
	{
		lx_check_quotes(flag, node->exp[i]);
		if (flag[0] && (!ft_isprint(node->exp[i]) || \
			node->exp[i] == '<' || node->exp[i] == '>'))
		{
			add_instruction(node, node->exp, from, &i);
			from = i;
		}
		i++;
	}
	add_instruction(node, node->exp, from, i);
}
