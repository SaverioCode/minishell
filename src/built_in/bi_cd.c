/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 23:01:46 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/06/21 00:38:56 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cd_home(t_info *info)
{
	char	*str;
	char	*value;

	str = ms_get_env_line(info->env, "HOME");
	value = ms_get_env_value(str, "HOME");
	if (chdir(value) == -1)
	{
		return (-1);
	}
	free(value);
	return (0);
}

int	bi_cd(t_info *info, char **args)
{
	if (ft_biarrlen(args) > 1)
	{
		write(2, "Error: to many arguments.\n", 26);
		return (1);
	}
	if (args == NULL)
	{
		if (cd_home(info) == -1)
		{
			write(2, "Error: HOME not found.\n", 23);
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
