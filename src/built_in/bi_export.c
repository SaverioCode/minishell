/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:13:48 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/07/14 20:22:46 by fgarzi-c         ###   ########.fr       */
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

__int8_t	bi_export(t_info *info, char **args)
{
	__int32_t	i;
	__int8_t	status;

	if (args == NULL)
	{
		print_all_vars(info->env);
		return (0);
	}
	status = 0;
	i = 0;
	while (args[i])
	{
		if (!ft_isalpha(args[i][0]) && !ft_isdigit(args[i][0]))
		{
			write(2, "Error: invalid name.\n", 21);
			status = 1;
		}
		else
		{
			bi_add_export_var(info, args[i], &status);
		}
		i++;
	}
	return (status);
}
