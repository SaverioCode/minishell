/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:42:02 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/06/23 15:11:31 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_node(t_env *node)
{
	free(node->name);
	free(node->value);
	free(node);
}

int	unset_node(t_info *info, char **args, t_env *node, t_env *tmp)
{
	int		count;
	int		i;

	i = 0;
	count = 0;
	while (args[i])
	{
		if (ft_strictcmp(node->name, args[i]) == 0)
		{
			count++;
			if (info->env == node)
			{
				info->env = info->env->next;
			}
			else
			{
				tmp->next = node->next;
			}
			free_node(node);
		}
		i++;
	}
	return (count);
}

int	bi_unset(t_info *info, char **args)
{
	t_env	*node;
	t_env	*tmp;
	int	count;

	if (args == NULL)
	{
		return (0);
	}
	count = 0;
	node = info->env;
	while (node)
	{
		count += unset_node(info, args, node, tmp);
		tmp = node;
		node = node->next;
	}
	if (count == 0)
	{
		write(2, "Error: variable not found.\n", 27);
		return (127);
	}
	return (0);
}
