/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separete_nodes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 23:15:57 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/12 06:42:22 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*cut_exp(t_node *node, t_info *info, int end)
{
	char	*str;
	char	*expr;
	int		i;
	int		j;
	char	len;

	if (!info->current_input)
		return (NULL);
	if (node->token == END)
	{
		node->exp = info->current_input;
		return (NULL);
	}
	expr = ft_calloc(i, 1);
	i = 0;
	while (i < end)
	{
		expr[i] = info->current_input[i];
		i++;
	}
	node->exp = expr;
	str = ft_calloc((ft_strlen(input) - i) + 1, 1);
	j = 0;
	while (input[i + j])
	{
		str[j] = input[i + j];
		j++;
	}
	free(input);
	return (str);
}

static t_node	*create_new_node(t_node *node, t_info *info)
{
	t_node	*new_node;
	t_node	*new_exps;

	if (node->token == END)
		return (NULL);
	new_node = ft_calloc(1, sizeof(t_node));
	new_exps = ft_calloc(1, sizeof(t_node));
	node->next = new_node;
	new_node->exps = new_exps;
	set_tnode(new_node);
	set_tnode(new_exps);
	return (new_node);
}

static int	check_exps_exp(t_node *node)
{
	int		i;
	char	*str;

	if (node->token != END)
		return (0);
	str = node->exps->exp;
	while (str[i])
	{
		if (is_printable(str[i]))
			return (0);
		i++;
	}
	// write error I think highlighting that current token is invalid //
	// to be sure check bash error handling in this situation //
	return (-1);
}

static int	get_token_and_exp(t_node *node, t_info *info, int i)
{
	int	status;

	if (get_token(node, info, i) == -1)
		return (-1);
	cut_exp(node, info, i);
	cut_token(node, info);
	update_current_input(node, info);
	status = check_exp(node);
	return (status);
}
