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

static char	get_token(t_node *node, char *input)
{
	int		i;
	char	token;
	char	len;

	token = 0;
	len = ft_strlen(input);
	i = 0;
	if (len > 1)
	{
		if (input[i] == 38 && input[i + 1] == 38)
			node->token = AND;
		else if (input == 124 && input[i + 1] == 124)
			node->token = OR;
		else if (input == 124 && !is_printable(input[i + 1]))
			node->token = PIPE;
	}
	if (len == 1)
	{
		if (input == 124)
			node->token = PIPE;
	}
	return (token);
}

static char	*create_new_node(t_node *node, char *input)
{
	t_node	*new_node;
	char	*str;

	new_node = ft_calloc(1, sizeof(t_node));
	node->next = new_node;
	str = get_token(new_node, input);
	free(input);
	return (str);
}

void	ft_separete_exps(t_node *node, char *input)
{
	int	i;
	int	flag[2];

	if (!node)
		return ;
	flag[0] = 0;
	i = 0;
	while (input[i])
	{
		check_flag(flag, input[i]);
		if (!flag[0] && (input[i] == 38 || input[i] == 124 || !input[i + 1]))
		{
			node = ls_get_last_node(node);
			input = cut_exp(node, input, i);
			if (input[i + 1])
			{	
				input = create_new_node(node, input);
			}
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
