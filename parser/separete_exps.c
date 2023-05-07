/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separete_exps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sav <sav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 23:15:57 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/07 03:28:05 by sav              ###   ########.fr       */
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
		return (NULL);
	expr = ft_calloc(i, 1);
	i = 0;
	while (i < end)
	{
		expr[i] = input[i];
		i++;
	}
	node->exps->exp = expr;
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

static void	create_new_node(t_node *node, t_input *input)
{
	t_node	*new_node;

	new_node = ft_calloc(1, sizeof(t_node));
	node->next = new_node;
	new_node->token = NULL;
	new_node->status = 0;
	new_node->fd_output = 0;
	new_node->exps = NULL;
	new_node->next = NULL;
	get_token(new_node, input);
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
				create_new_node(node, input);
			str = input->current;
			if (!str)
				break ;
			i = -1;
		}
		i++;
	}
	if (flag[0])
	{
		ft_free(node, input);
		write(2, "Error: quotes or parentesi\n", 27);
		exit(1);
	}
}
