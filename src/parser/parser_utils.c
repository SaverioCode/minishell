/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 06:57:18 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/12 10:33:52 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	append_opr(t_node *node, t_opr *opr)
{
	t_opr	*opr;

	opr = node->opr;
	if (!opr)
	{
		node->opr = opr;
		return ;
	}
	while (opr->next)
	{
		opr = opr->next;
	}
	opr->next = opr;
}

static void	update_opr(t_node *node, int fd_len, int *i)
{
	t_opr	*opr;

	opr	= create_opr();
	append_opr(node, opr);
}

void	organize_exp(t_node *node)
{
	char	*exp;
	int		i;
	int		len;
	int		print;

	exp = node->exp;
	i = 0;
	len = 0;
	while (exp[i])
	{
		if (exp[i] == '<' || exp[i] == '>')
		{
			create_opr(node, len, &i);
			get_fd();
			get_opr();
			get_arg();
			continue ;
		}
		print = ft_isprint(exp[i]);
		if (!print && len)
		{
			update_cmd();
		}
		else if (print)
		{
			len++;
		}
		i++;
	}
	free(node->exp);
}
