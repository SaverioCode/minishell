/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 23:15:57 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/22 10:40:41 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	get_token(char *input)
{
	if (input[0] == '&' && input[1] == '&')
	{
		input[0] = 0;
		input[1] = 1;
		return (AND);
	}
	else if (input[0] == '|' && input[1] == '|')
	{
		input[0] = 0;
		input[1] = 1;
		return (OR);
	}
	else if (input[0] == '|')
	{
		input[0] = 0;
		return (PIPE);
	}
	return (0);
}

static t_node	*create_subshell(t_node *node)
{
	t_node *subshl;

	subshl = ft_calloc(1, sizeof(t_node));
	init_tnode(subshl);
	node->subshl = subshl;
	subshl->back = node;
	return (subshl);
}

static t_node	*create_new_node(t_node *node, char *input)
{
	t_node	*new_node;

	if (input[1] == 0)
		return (NULL);
	new_node = ft_calloc(1, sizeof(t_node));
	init_tnode(new_node);
	node->next = new_node;
	new_node->back = node;
	return (new_node);
}

void	ft_parser(t_node *node, char *input)
{
	int	flag[2];
	int	from;
	int	i;

	flag[0] = 0;
	from = 0;
	i = 0;
	while (input && input[i])
	{
		lx_check_quotes(flag, input[i]);
		if (!flag[0])
		{
			if (input[i] == '(')
			{
				// write(1, "P3\n", 3);////////
				input[i] = 32;
				node = create_subshell(node);
			}
			else if (input[i] == ')')
			{
				// write(1, "P4\n", 3);////////
				input[i] = 32;
				organize_exp(node, ft_getstr_from_to(input, from, i));
				node = node->back;
				from = i + 1;
			}
			else if (input[i] == '&' || input[i] == '|' || input[i + 1] == 0)
			{	
				// write(1, "P5\n", 3);////////
				node->token = get_token(&input[i]);
				organize_exp(node, ft_getstr_from_to(input, from, i));
				// write(1, "P6\n", 3);////////
				node = create_new_node(node, &input[i]);
				from = i + 1;
			}
		}
		i++;
		// write(1, "P1\n", 3);////////
		// write(1, "P2\n", 3);////////
	}
}
