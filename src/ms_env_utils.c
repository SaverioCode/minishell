/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 00:08:10 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/06/21 18:59:18 by fgarzi-c         ###   ########.fr       */
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

void	ms_set_env(t_info *info, char **env)
{
	t_env	*node;
	t_env	*new;
	int		i;

	i = 0;
	node = NULL;
	info->env = node;
	if (env == NULL)
	{
		return ;
	}
	i = 0;
	while (env[i])
	{
		new = ft_calloc(1, sizeof(t_env));
		new->name = NULL;
		new->value = NULL;
		new->next = NULL;
		new->name = extract_env_name(env[i]);
		new->value = extract_env_value(env[i], new->name);
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


