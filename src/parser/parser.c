/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 23:15:57 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/12 06:48:56 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_node	*create_subshell(t_node *node)
{
	t_node *subshl;

	subshl = ft_calloc(1, 8);
	set_tnode(subshl);
	subshl->back = node;
	return (subshl);
}

void	ft_parser(t_node *node, char *input)
{
	int	flag[2];
	int	i;

	flag[0] = 0;
	flag[1] = 0;
	i = 0;
	while (input && input[i])
	{
		lx_check_quotes(flag, input[i]);
		if (!flag[0])
		{
			if (input[i] == '(')
				node = create_subshell(node);
			else if (input[i] == ')')
				node = node->back;
			else if (input[i] == '&' || input[i] == '|' || input[i + 1] == 0)
			{	
				cut_exp(node, input, i);
				orginize_exp(node);
				node = create_new_node(node, input, i);
				cut_token(input, i);  // maybe not needed
				i = -1;
			}
		}
		i++;
	}
}
