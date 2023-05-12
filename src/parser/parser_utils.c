/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 06:57:18 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/12 12:46:50 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_opr(t_node *node)
{
	t_opr	*new_opr;
	t_opr	*opr;

	new_opr = ft_calloc(1, 8);
	set_topr(new_opr);
	opr = node->opr;
	if (!opr)
	{
		node->opr = new_opr;
		return ;
	}
	while (opr->next)
	{
		opr = opr->next;
	}
	opr->next = new_opr;
}

static void	update_opr(t_node *node, char *fd, int *i)
{
	t_opr	*opr;
	char	*str;
	int		start;
	int		end;

	opr = ft_calloc(1, 8);
	set_topr(opr);
	if (fd)
	{
		opr->fd = ft_atoi(fd);
		free(fd);
	}
	opr->token = lx_which_token(&node->exp[*i]);
	if (opr->token == INP || opr->token == OUT)
		start = *i + 1;
	else if (opr->token == HDOC || opr->token == APP)
		start = *i + 2;
	end = start;
	while (ft_isprint(node->exp))
	{
		end++;
	}
	opr->arg = get_str(node->exp, end - start, end);
	*i = end + 1;
	append_opr(node, opr);
}

void	organize_exp(t_node *node)
{
	char	*exp;
	char	*str;
	int		i;
	int		len;
	int		print;

	exp = node->exp;
	i = 0;
	len = 0;
	while (exp[i])
	{
		while (ft_isprint(exp[i]))
		{
			len++;
			i++;
			if (exp[i] == '<' || exp[i] == '>')
			{
				create_opr(node);
				if (len > 1)
				{
					str = get_str(exp, len, i);
					if (ft_str_isdigit(str));
				}
			}
		}
		len = 0;
		i++;
		// if (exp[i] == '<' || exp[i] == '>')
		// {
		// 	update_opr(node, len, &i);
		// 	len = 0;
		// 	continue ;
		// }
		// print = ft_isprint(exp[i]);
		// if (!print && len)
		// {
		// 	update_cmd();
		// 	len = 0;
		// }
		// else if (print)
		// {
		// 	len++;
		// }
		// i++;
	}
	free(node->exp);
}
