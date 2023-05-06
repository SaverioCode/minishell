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

	if (!input)
		return (NULL); // magari free e return //
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

static char	*create_new_node(t_node *node, t_input *input)
{
	t_node	*new_node;
	char	*str;

	new_node = ft_calloc(1, sizeof(t_node));
	node->next = new_node;
	get_token(new_node, input);
	free(input);
	return (str);
}

void	ft_separete_exps(t_node *node, t_input *input)
{
	char	*str;
	int		i;
	int		flag[2];

	if (!node)
		return ;
	input = input->starting;
	flag[0] = 0;
	i = 0;
	while (str[i])
	{
		check_flag(flag, str[i]);
		if (!flag[0] && (str[i] == 38 || str[i] == 124 || !str[i + 1]))
		{
			node = ls_get_last_node(node);
			input->current = cut_exp(node, input, i);
			if (str[i + 1])
			{	
				str = create_new_node(node, input);
			}
			str = input->current;
			i = -1;
			if (!input)
				break ;
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
