/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organize_exp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 06:57:18 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/27 14:37:50 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ps_organize_exp(t_node *node, char *exp)
{
	int		from;
	int		i;
	int		flag[2];

	flag[0] = 0;
	from = 0;
	while (exp[from])
	{	
		if (ft_isprint(exp[from]))
			break ;
		from++;
	}
	i = from;
	while (exp[i])
	{
		lx_check_quotes(flag, exp[i]);
		if (!flag[0] && (!ft_isprint(exp[i]) || exp[i] == '<' || exp[i] == '>'))
		{
			if (from < i)
			{
				add_instruction(node, exp, from, &i);
			}
			from = i + 1;
		}
		i++;
	}
	exp = ft_trim(&exp[from], exp);
	i = ft_strlen(exp);
	add_instruction(node, exp, 0, &i);
	free(exp);
}
