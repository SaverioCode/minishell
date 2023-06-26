/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sav <sav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 00:41:23 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/06/26 22:08:32 by sav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_env(t_env *node, char **args)
{
	if (args != NULL)
	{
		write(2, "Error: to many arguments.\n", 26);
		return (127);
	}
	while (node)
	{
		if (node->env == 1)
		{
			write(1, node->name, ft_strlen(node->name));
			if (node->value)
			{
				write(1, "=", 1);
				write(1, node->value, ft_strlen(node->value));
				write(1, "\n", 1);
			}
		}
		node = node->next;
	}
	return (0);
}
