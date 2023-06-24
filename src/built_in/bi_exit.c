/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sav <sav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 00:44:41 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/06/24 09:46:13 by sav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			status = ft_atoi(args[0]);
			exit(status);
		}
		write(1, "Error: argument has to be a number.\n", 36);
		return (1);
	}
	status = info->status;
	rl_clear_history();
	ms_free_childs(info->child);
	ms_restore_fd(info);
	ms_free(info->root, info);
	exit(status);
}
