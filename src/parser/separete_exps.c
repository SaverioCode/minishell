/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separete_exps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 23:15:57 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/09 18:03:09 by fgarzi-c         ###   ########.fr       */
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

static t_node	*create_new_node(t_node *node, t_info *info)
{
	t_node	*new_node;

	if (node->token == END)
		return (NULL);
	new_node = ft_calloc(1, sizeof(t_node));
	node->next = new_node;
	set_tnode(node);
	return (new_node);
}

int	ft_separete_exps(t_node *root, t_info *info, int *flag)
{
	t_node	*node;
	char	*str;
	int		i;

	node = root;
	str = info->starting_input;
	i = 0;
	while (str[i])
	{
		check_flag(flag, str[i]);
		if (!flag[0] && (str[i] == 38 || str[i] == 124 || !str[i + 1]))
		{
			info->current_input = cut_exp(node, str, i);
			if (get_token(node, info) == -1)
				return (-1);
			if (ft_create_exps_tree(node) == -1)
				return (-1);
			if (node->token)
				node = create_new_node(node, info);
			str = info->current_input;
			// if (!str)
			// 	break ;
			i = -1;
		}
		i++;
	}
}
