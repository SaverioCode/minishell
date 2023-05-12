/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 23:15:57 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/12 09:47:21 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void *cut_exp(t_node *node, char *input, int end)
{
	char		*str;
	static int	start;

	if (input[end] != '&' && input[end] != '|')
		end++;
	str = ft_calloc(end, 1);
	while (start < end)
	{
		str[start] = input[start];
		start++;
	}
	node->exp = str;
}

static t_node	*create_subshell(t_node *node)
{
	t_node *subshl;

	subshl = ft_calloc(1, 8);
	set_tnode(subshl);
	node->subshl = subshl;
	subshl->back = node;
	return (subshl);
}

static t_node	*create_new_node(t_node *node, char *input, int *i)
{
	t_node	*new_node;

	if (input[1] == 0)
		return (NULL);
	if (input[0] == '&' && input[1] == '&')
	{	
		node->token = AND;
		*i += 2;
	}
	else if (input[0] == '|' && input[1] == '|')
	{	
		node->token == OR;
		*i += 2;
	}
	else if (input[0] == '|')
	{	
		node->token == PIPE;
		*i += 1;
	}
	new_node = ft_calloc(1, 8);
	set_tnode(new_node);
	node->next = new_node;
	new_node->back = node;
	return (new_node);
}

void	ft_parser(t_node *node, char *input)
{
	int	flag[2];
	int	i;

	flag[0] = 0;
	i = 0;
	while (input && input[i])
	{
		lx_check_quotes(flag, input[i]);
		if (!flag[0])
		{
			if (input[i] == '(')
			{
				input[i] = 32;
				node = create_subshell(node);
			}
			else if (input[i] == ')')
			{
				input[i] = 32;
				node = node->back;
			}
			else if (input[i] == '&' || input[i] == '|' || input[i + 1] == 0)
			{	
				cut_exp(node, input, i);
				orginize_exp(node);
				node = create_new_node(node, &input[i], &i);
			}
		}
		i++;
	}
}
