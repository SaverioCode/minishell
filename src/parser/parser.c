/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 23:15:57 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/12 06:38:03 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parser(t_node *node, char *input)
{
	int	flag[2];
	int	i;

	flag[0] = 0;
	flag[1] = 0;
	i = 0;
	while (input[i])
	{
		lx_check_quotes(flag, input[i]);
		if (!flag[0])
		{
			if (input[i] == '(')
				create_subshell(node);
			if (input[i] == ')')
				get_back(node);
			if (input[i] == '&' || input[i] == '|')
			{	
				cut_exp(node, input, i);
				orginize_exp(node);
				create_new_node(node, input, i);
				cut_token(input, i);
			}
		}
		i++;
	}
}
