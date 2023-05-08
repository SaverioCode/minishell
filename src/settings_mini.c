/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_mini.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:24:01 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/08 11:26:01 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_tenv(t_env *node)
{
	node->name = NULL;
	node->value = NULL;
	node->next = NULL;
}

void	set_tinfo(t_info *info)
{
	info->env = NULL;
	info->starting_input = NULL;
	info->current_input = NULL;
}
