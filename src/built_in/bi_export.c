/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:13:48 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/06/21 23:21:30 by fgarzi-c         ###   ########.fr       */
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

static int	check_arg(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((ft_isalpha(str[i]) == 1  && str[i + 1] != '+' ) || !ft_isprint(str[i]))
		{
			write(2, "Error: invalid name.\n", 21);
			return (-1);
		}
		i++;
	}
	return (1);
}

static void	add_export_var(t_info *info, char *str, int *status)
{
	if (check_arg(str) == -1)
	{
		*status = 1;
	}
	
}

int	bi_export(t_info *info, char **args)
{
	int	i;
	int	status;

	if (args == NULL)
	{
		print_all_vars(info->env);
		return (0);
	}
	status = 0;
	i = 0;
	while (args[i])
	{
		// status = check_arg(args[i]);
		if (ft_find_char(args[i], '=') == 1)
		{
			add_export_var(info, args[i], &status);
		}
		else if (status == 0)
		{
			add_env_var(info, args[i], &status);
		}
		i++;
	}
	return (0);
}
