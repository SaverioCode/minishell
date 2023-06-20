/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 23:01:46 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/06/21 00:24:23 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char *get_home(t_info *info)
// {
// 	while ()
// }

int	bi_cd(char **args)
{
	if (ft_biarrlen(args) > 1)
	{
		write(2, "Error: to many arguments.\n", 26);
		return (1);
	}
	if (args == NULL)
	{
		if (chdir(NULL) == -1)
		{
			write(2, "Error: no entry point.\n", 23);
			return (1);
		}
	}
	else if (chdir(args[0]) == -1)
	{
		if (chdir(get_cwd()) == -1)
		{
			write(2, "Error: directory not found.\n", 28);
			return (1);
		}
	}
	return (0);
}
