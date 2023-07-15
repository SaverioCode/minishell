/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 00:44:41 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/07/15 23:21:09 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_childs(t_child *node)
{
	t_child	*tmp;

	while (node)
	{
		tmp = node;
		node = node->next;
		free(tmp);
	}
}

static __int32_t	get_status(char *num)
{
	__int32_t	status;

	status = ft_atoi(num);
	status = status % 256;
	return (status);
}

int	bi_exit(t_info *info, char **args)
{
	int	status;
	int	arg_len;

	arg_len = ft_biarrlen(args);
	if (arg_len > 1)
	{
		write(1, "Error: to many arguments.\n", 26);
		return (1);
	}
	if (arg_len == 1)
	{
		if (ft_str_isdigit(args[0]))
		{
			status = get_status(args[0]);
			exit(status);
		}
		write(1, "Error: argument has to be a number.\n", 36);
		return (1);
	}
	status = info->exit_status % 256;
	rl_clear_history();
	free_childs(info->child);
	ms_restore_fd(info);
	ms_free(info->root, info);
	exit(status);
}
