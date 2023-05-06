/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 23:15:57 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/05 00:14:38 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	check_flag(int *flag, char c)
{
	if (c == 34 || c == 96 || c == 28 || c == 29)
	{
		if (flag[0])
		{	
			if ((flag[1] == 28 && c == 29) || (flag[1] != 28 && c == flag[1]))
			{
				flag[0] = 0;
				flag[1] = 0;
			}
		}
		else if (!flag[0] && c != 29)
		{
			flag[0] = 1;
			flag[1] = c;
		}
	}
}

static char	*cut_exp(t_node *node, char *input, int end)
{
	char	*str;
	char	*expr;
	int		i;
	int		j;
	char	len;

	expr = ft_calloc(i, 1);
	i = 0;
	while (i < end)
	{
		expr[i] = input[i];
		i++;
	}
	node->exp = expr;
	expr = ft_calloc((ft_strlen(input) - i) + 1, 1);
	j = 0;
	while (input[i])
	{
		str[j] = input[i];
		i++;
		j++;
	}
	free(input);
	return (str);
}

static void	create_new_node(t_node *node, char *input)
{
	t_node	new_node;

	new_node = ft_calloc(1, sizeof(t_node));
	
}

void	ft_separete_exps(t_node *node, char *input)
{
	int	i;
	int	flag[2];

	flag[0] = 0;
	i = 0;
	while (input[i])
	{
		check_flag(flag, input[i]);
		if (!flag[0] && (input[i] == 26 || input[i] == 124))
		{
			input = cut_exp(node, input, i);
			create_new_node(node, input);
			i = 0;
			continue ;
		}
		i++;
	}
	if (flag[0])
	{
		write(2, "Error: quotes or parentesi\n", 27);
		// friare tutto //
		exit(1);
	}
}
