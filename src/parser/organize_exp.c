/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organize_exp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 06:57:18 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/26 08:40:45 by fgarzi-c         ###   ########.fr       */
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

	str = ft_getstr_from_to(exp, from, *i - 1);
	printf("|%s|\n", str);///////////
	if (exp[*i] == '<' || exp[*i] == '>')
	{
		write(1, "ADINS1\n", 7);/////////
		opr = create_opr(node);
		if (ft_str_isdigit(str))
		{
			opr->fd = ft_atoi(str);
			free(str);
			return ;
		}
		// else
		// {
		// 	write(1, "ADINS2\n", 7);/////////
		// 	add_to_cmd(node, str);
		// 	return ;
		// }
		opr->token = lx_which_token(&exp[*i]);
		if (opr->token == HDOC || opr->token == APP)
			*i += 1;
	}
	write(1, "ADINS4\n", 7);/////////
	add_to_cmd(node, str);
}

void	organize_exp(t_node *node, char *exp)
{
	int		from;
	int		i;
	int		flag[2];

	flag[0] = 0;
	from = 0;
	// printf("|%s|\n", exp);/////////
	// write(1, "OEXP0\n", 6);////////
	while (exp[from])
	{	
		if (ft_isprint(exp[from]))
			break ;
		from++;
	}
	// printf("|%d|\n", from);///////
	i = from;
	while (exp[i])
	{
		lx_check_quotes(flag, exp[i]);
		if (!flag[0] && (!ft_isprint(exp[i]) || exp[i] == '<' || exp[i] == '>'))
		{
			// write(1, "OEXP1\n", 6);////////
			if (from < i)
			{
				// write(1, "OEXP2\n", 6);////////
				add_instruction(node, exp, from, &i);
				write(1, "OEXP2\n", 6);////////
			}
			from = i + 1;
		}
		// write(1, "O1\n", 3);/////
		// printf("| %d |\n", i);////
		i++;
	}
	add_instruction(node, exp, from, &i);
	free(exp);
}
