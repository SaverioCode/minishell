/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 23:15:57 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/12 06:29:56 by fgarzi-c         ###   ########.fr       */
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
			handle_token(node, input, i);
			if (input[i] == '(')
			{
				create_subshell(node);
			}
		}
		i++;
	}
}
