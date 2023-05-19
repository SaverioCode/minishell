/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 23:15:57 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/19 06:11:23 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_token(t_node *node, char *input)
{
	char	token;
	int		size;
	t_node	*last;

	token = lx_which_token(input);
	if (token == AND || token == OR)
		size = 2;
	else if (token == PIPE)
		size = 1;
	last = ls_get_last_tnode(node, 's');
	if (!last->token)
		last->token = token;
	return (size);
}

static t_node* get_node(t_node *node)
{
	t_node	*subshl;

	subshl = ls_get_last_tnode(node, 's');
	if (!subshl->token && !subshl->exp)
		return (subshl);
}

static void *get_exp_and_token(t_node *node, char *input, int end)
{
	char		*str;
	static int	start;
	int			size;

	if (input[end] != '&' && input[end] != '|')
		end++;
	str = ft_calloc(end + 1, 1);
	while (start < end)
	{
		str[start] = input[start];
		start++;
	}
	size = get_token(node, &input[end]);
	start += size;
	node->exp = str;
}

static t_node	*create_subshell(t_node *node)
{
	t_node *subshl;

	subshl = ft_calloc(1, 8);
	init_tnode(subshl);
	node->subshl = subshl;
	subshl->back = node;
	return (subshl);
}

static t_node	*create_new_node(t_node *node, char *input, int *i)
{
	t_node	*new_node;

	if (input[1] == 0)
		return (NULL);
	// if (input[0] == '&' && input[1] == '&')
	// {	
	// 	node->token = AND;
	// 	*i += 2;
	// }
	// else if (input[0] == '|' && input[1] == '|')
	// {	
	// 	node->token == OR;
	// 	*i += 2;
	// }
	// else if (input[0] == '|')
	// {	
	// 	node->token == PIPE;
	// 	*i += 1;
	// }
	new_node = ft_calloc(1, 8);
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
				input[i] = 32;
				node = create_subshell(node);
			}
			else if (input[i] == ')')
			{
				input[i] = 32;
				cut_exp(node, input, i);
				organize_exp(node, ft_getstr_from_to(input, from, i));
				node = node->back;
				from = i + 1;
			}
			else if (input[i] == '&' || input[i] == '|' || input[i + 1] == 0)
			{	
				cut_exp(node, input, i);
				// I could call the function above get_exp_and_token //
				// I could assign token here //
				organize_exp(node, ft_getstr_from_to(input[i], from, i));
				node = create_new_node(node, &input[i], &i);
				from = i + 1;
			}
		}
		i++;
	}
}
