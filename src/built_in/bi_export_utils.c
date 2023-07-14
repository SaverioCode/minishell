/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 20:14:37 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/07/14 20:29:04 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
				node->env = 1;
			free(name);
			return (0);
		}
		node = node->next;
	}
	return (-1);
}

static void	add_node(t_info *info, char *name, char *value, int flag)
{
	t_env	*node;
	t_env	*new;

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

static __int8_t	accrocchio_norma(char *name, char *value, __int8_t *status)
{
	if (check_name(name, status) == -1)
	{
		write(2, "Error: invalid name.\n", 21);
		*status = 1;
		free(name);
		free(value);
		return (-1);
	}
	return (0);
}

void	bi_add_export_var(t_info *info, char *arg, __int8_t *status)
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
		name = ft_strcpy(arg);
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
	if (accrocchio_norma(name, value, status) == -1)
		return ;
	add_node(info, name, value, flag);
}
