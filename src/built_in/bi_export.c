/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:13:48 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/07/12 00:52:21 by fgarzi-c         ###   ########.fr       */
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

static __int8_t	check_name(char *str, __int8_t *status)
{
	__int32_t	i;

	i = 0;
	if (str == NULL)
	{
		return (-1);
	}
	while (str[i])
	{
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]))
		{
			*status = 1;
			return (-1);
		}
		i++;
	}
	return (0);
}

static __int8_t	update_node(t_env *node, char *name, char *value, int flag)
{
	while (node)
	{
		if (ft_strictcmp(node->name, name) == 0)
		{
			if (flag == 1)
			{
				node->value = ft_strjoin(node->value, value, 1, 1);
			}
			else
			{
				free(node->value);
				node->value = value;
			}
			if (node->value == NULL)
			{
				node->env = 0;
			}
			else
			{
				node->env = 1;
			}
			free(name);
			return (0);
		}
		node = node->next;
	}
	return (-1);
}

static void	add_node(t_info *info, char *name, char *value, int flag)
{
	t_env *node;
	t_env *new;

	node = info->env;
	if (update_node(node, name, value, flag) == 0)
	{
		return ;
	}
	while (node->next)
	{
		node = node->next;
	}
	new = ft_calloc(1, sizeof(t_env));
	new->name = NULL;
	new->name = name;
	new->value = NULL;
	new->value = value;
	new->env = 0;
	if (new->value != NULL)
	{
		new->env = 1;
	}
	node->next = new;
	new->next = NULL;
}

static void	add_export_var(t_info *info, char *arg, __int8_t *status)
{
	char		*name;
	char		*value;
	__int32_t	i;
	__int8_t	flag;

	value = NULL;
	name = NULL;
	flag = 0;
	i = ft_find_char(arg, '=');
	if (i == -1)
	{
		name = ft_strcpy(arg);
	}
	else if (arg[i - 1] == '+' && arg[i] == '=')
	{
		flag = 1;
		name = ft_getstr_from_to(arg, 0, i - 2);
		value = ft_getstr_from_to(arg, i + 1, ft_strlen(arg) - 1);
	}
	else if (arg[i] == '=')
	{
		name = ft_getstr_from_to(arg, 0, i - 1);
		value = ft_getstr_from_to(arg, i + 1, ft_strlen(arg) - 1);
	}
	if (check_name(name, status) == -1)
	{
		write(2, "Error: invalid name.\n", 21);
		*status = 1;
		free(name);
		free(value);
		return ;
	}
	add_node(info, name, value, flag);
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
			add_export_var(info, args[i], &status);
		}
		i++;
	}
	return (status);
}
