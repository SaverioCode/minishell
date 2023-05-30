/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organize_exp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 06:57:18 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/27 20:55:52 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ps_organize_exp(t_node *node, char *exp)
{
	int		from;
	int		i;
	int		flag[2];

	flag[0] = 0;
	from = ft_find_printable(exp, '+');
	i = from;
	while (exp[i])
	{
		lx_check_quotes(flag, exp[i]);
		if (!flag[0] && (!ft_isprint(exp[i]) || exp[i] == '<' || exp[i] == '>'))
		{
			if (from <= i)
			{
				ps_add_instruction(node, exp, from, &i);
			}
			from = i + 1;
		}
		i++;
	}
	exp = ft_trim(&exp[from], exp);
	i = ft_strlen(exp);
	ps_add_instruction(node, exp, 0, &i);
}
