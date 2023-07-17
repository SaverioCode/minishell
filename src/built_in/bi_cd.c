/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 23:01:46 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/07/17 13:43:38 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_oldpwd(t_info *info)
{
	t_env	*env;
	t_env	*new;

	env = info->env;
	while (env)
	{
		if (ft_strictcmp(env->name, "OLDPWD") == 0)
		{
			free(env->value);
			env->value = ms_get_env_value(info, "PWD");
			break ;
		}
		env = env->next;
	}
	if (env == NULL)
	{
		new = ft_calloc(1, sizeof(t_env));
		new->next = NULL;
		new->env = 0;
		new->name = ft_strcpy("OLDPWD");
		new->value = ms_get_env_value(info, "PWD");
		env->next = new;
	}
}

static void	update_env(t_info *info, char *cwd)
{
	t_env	*env;

	update_oldpwd(info);
	env = info->env;
	while (env)
	{
		if (ft_strictcmp(env->name, "PWD") == 0)
		{
			free(env->value);
			env->value = ft_strcpy(cwd);
		}
		env = env->next;
	}
	free(cwd);
}

static int	cd_home(t_info *info)
{
	char	*value;

	value = ms_get_env_value(info, "HOME");
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
		if (chdir(bi_get_cwd()) == -1)
		{
			write(2, "Error: directory not found.\n", 28);
			return (1);
		}
	}
	update_env(info, bi_get_cwd());
	return (0);
}
