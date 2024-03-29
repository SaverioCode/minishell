/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 09:43:41 by sav               #+#    #+#             */
/*   Updated: 2023/07/13 22:41:00 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_env(t_env *node)
{
	t_env	*tmp;

	while (node)
	{
		free(node->name);
		free(node->value);
		tmp = node;
		node = node->next;
		free(tmp);
	}
}

void	ms_free_info(t_info *info)
{
	if (info->env)
	{
		free_env(info->env);
	}
	if (info->input)
	{
		free(info->input);
	}
	if (info->prompt)
	{
		free(info->prompt);
	}
	close(info->stdin_clone);
	close(info->stdout_clone);
	free(info);
}
