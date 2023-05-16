/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 23:49:40 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/17 01:11:00 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*create_s_env(t_env *env)
{
	t_env	*new_env;

	new_env = ft_calloc(8, 1);
	init_tenv(new_env);
	env->next = new_env;
	return (new_env);
}

static void	get_name_and_vale(char *str, t_env *env)
{
	int		i;
	int		len;

	i = ft_strchr(str, '=');
	len = ft_strlen(str);
	if (i == len)
	{
		env->name = str;
		return ;
	}
	env->name = ft_getstr_from_to(str, 0, i - 1);
	env->value = ft_getstr_from_to(str, i + 1, len);
}

void	ft_set_starting_env(char **env, t_info *info)
{
	t_env	*env_s;
	size_t	i;

	if (!env || !env[0])
		return ;
	env_s = ft_calloc(8, 1);
	init_tenv(env_s);
	info->env = env_s;
	i = 0;
	while (env[i])
	{
		get_name_and_vale(env[i], env_s);
		if (env[i + 1])
		{	
			env_s = create_s_env(env_s);
		}
		i++;
	}
}
