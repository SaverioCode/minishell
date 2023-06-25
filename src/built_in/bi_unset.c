/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sav <sav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:42:02 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/06/25 20:52:20 by sav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_node(t_env *node)
{
	free(node->name);
	free(node->value);
	free(node);
}

static void	check_nodes(t_info *info, char *arg)
{
	t_env	*node;
	t_env	*tmp;

	node = info->env;
	while (node->next)
	{
		tmp = node->next;
		if (ft_strictcmp(tmp->name, arg) == 0)
		{
			node->next = tmp->next;
			free_node(tmp);
			return ;
		}
		node = node->next;
	}
	return ;
}

static int	check_head(t_info *info, char *arg)
{
	t_env	*head;

	head = info->env;
	if (ft_strictcmp(head->name, arg) == 0)
	{
		info->env = head->next;
		free_node(head);
		return (0);
	}
	return (-1);
}

int	bi_unset(t_info *info, char **args)
{
	int		i;

	if (args == NULL || info->env == NULL)
	{
		return (0);
	}
	i = 0;
	while (args[i])
	{
		if (check_head(info, args[i]) == -1)
		{
			check_nodes(info, args[i]);
		}
		i++;
	}
	return (0);
}
