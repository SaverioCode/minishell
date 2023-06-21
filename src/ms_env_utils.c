/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 00:08:10 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/06/21 19:55:38 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extract_env_value(char *str, char *name)
{
	char	*var;
	int		name_len;

	name_len = ft_strlen(name);
	if (str[name_len] == '=')
	{
		var = ft_strcpy(&str[name_len + 1]);
		return (var);
	}
	return (NULL);
}

static char	*extract_env_name(char *str)
{
	char	*name;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i + 1] == '=' || str[i + 1] == 0)
		{
			name = ft_getstr_from_to(str, 0, i);
			return (name);
		}
		i++;
	}
	return (NULL);
}

char	*ms_get_env_value(t_info *info, char *name)
{
	t_env	*node;
	char	*value;
	int		name_len;

	name_len = ft_strlen(name);
	node = info->env;
	while (node)
	{
		if (node->name)
		{
			if (ft_strictcmp(node->name, name) == 0)
			{
				value = ft_strcpy(node->value);
				return (value);
			}
		}
		node = node->next;
	}
	return (NULL);
}

static t_env	*create_env_node(char *str)
{
	t_env	*node;

	node = ft_calloc(1, sizeof(t_env));
	node->env = 0;
	node->name = NULL;
	node->value = NULL;
	node->next = NULL;
	node->env = 1;
	node->name = extract_env_name(str);
	node->value = extract_env_value(str, node->name);
	return (node);
}

void	ms_set_env(t_info *info, char **env)
{
	t_env	*node;
	t_env	*new;
	int		i;

	node = NULL;
	info->env = node;
	if (env == NULL)
	{
		return ;
	}
	i = 0;
	while (env[i])
	{
		new = create_env_node(env[i]);
		if (info->env != NULL)
		{
			node->next = new;
			node = node->next;
		}
		else
		{
			info->env = new;
			node = new;
		}
		i++;
	}
}


