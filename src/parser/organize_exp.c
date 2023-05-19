/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organize_exp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 06:57:18 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/19 20:21:21 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_opr	*create_opr(t_node *node)
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

/// perche minchia ho questa funzione se invece ///
/// qualche riga piu sotto ne chiamo una anloga ///
/// che invece sta in un altro foglio ??? ///
/// magari i resti di una vita passata ///
/// oppure la soluzione finale ///
// static t_opr	*get_last_opr(t_node *node)
// {
// 	t_opr	*opr;

// 	opr = node->opr;
// 	while (opr->next)
// 	{
// 		opr = opr->next;
// 	}
// 	if (!opr->arg)
// 	{	
// 		return (opr);
// 	}
// 	opr->next = ft_calloc(8, 1);
// 	init_topr(opr->next);
// 	return (opr->next);
// }

static void	add_to_cmd(t_node *node, char *str)
{
	char	**new_args;
	size_t	i;

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
	new_args = ft_calloc(8, i + 2);
	new_args[i + 1] = str;
	while (i >= 0)
	{
		new_args[i] = node->cmd->args[i];
		i--;
	}
	free(node->cmd->args);
	node->cmd->args = new_args;
}

static void	add_instruction(t_node *node, char *exp, int from, int *i)
{
	char	*str;
	t_opr	*opr;

	str = ft_getstr_from_to(exp, from, *i);
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
		}
		opr->token = lx_which_token(&exp[*i]);
		if (opr->token == HDOC || opr->token == APP)
			*i += 1;
	}
	opr = ls_get_last_topr(node->opr);
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
		if (flag[0] && (!ft_isprint(exp[i]) || \
			exp[i] == '<' || exp[i] == '>'))
		{
			if (from < i)
			{
				add_instruction(node, exp, from, &i);
			}
			from = i + 1;
		}
		// write(1, "O1\n", 3);/////
		// printf("| %d |\n", i);////
		i++;
	}
	// add_instruction(node, exp, from, &i);
	free(exp);
}
