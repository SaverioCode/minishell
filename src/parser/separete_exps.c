/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separete_exps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 23:15:57 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/08 13:21:48 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	create_new_node(t_node *node, t_info *info)
{
	t_node	*new_node;

	new_node = ft_calloc(1, sizeof(t_node));
	node->next = new_node;
	set_tnode(node);
	get_token(new_node, info);
}

void	ft_separete_exps(t_node *node, t_info *info)
{
	char	*str;
	int		i;
	int		flag[2];

	if (!node || !info)
		return ;
	str = info->starting_input;
	flag[0] = 0;
	i = 0;
	while (str[i])
	{
		check_flag(flag, str[i]);
		if (!flag[0] && (str[i] == 38 || str[i] == 124 || !str[i + 1]))
		{
			node = ls_get_last_tnode(node);
			info->current_input = cut_exp(node, str, i);
			if (str[i + 1])
				create_new_node(node, info);
			// insert here $ expansion //
			// insert here parentesi check and tree //
			str = info->current_input;
			if (!str)
				break ;
			i = -1;
		}
		i++;
	}
	if (flag[0])
	{
		ft_free(node, info);
		write(2, "Error: quotes or parentesi\n", 27);
		exit(1);
	}
}
