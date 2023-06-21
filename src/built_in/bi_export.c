/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:13:48 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/06/21 19:58:51 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_all_vars(t_env *node)
{
	while (node)
	{
		write(1, node->name, ft_strlen(node->name));
		if (node->value)
		{
			write(1, "=", 1);
			write(1, node->value, ft_strlen(node->value));
		}
		write(1, "\n", 1);
		node = node->next;
	}
}

int	bi_export(t_info *info, char **args)
{
	if (args == NULL)
	{
		print_all_vars(info->env);
		return (0);
	}
}
