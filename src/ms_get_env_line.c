/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_env_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 00:08:10 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/06/21 00:31:29 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_get_env_value(char *str, char *name)
{
	char	*var;
	int		name_len;

	name_len = ft_strlen(name);
	if (str[name_len] == '=')
	{
		var = ft_strcpy(&str[name_len + 1]);
		return (var);
	}
	return (NULL);
}

char	*ms_get_env_line(char **env, char *str)
{
	int	i;
	int	len;
	int	str_len;

	i = 0;
	while (env[i])
	{
		len = ft_strlen(env[i]);
		if (len >= 6)
		{
			str_len = ft_strlen(str);
			if (ft_strncmp(env[i], str, str_len) == 1)
			{
				if (env[i][str_len] == 0 || env[i][str_len] == '=')
				{
					return (env[i]);
				}
			}
		}
		i++;
	}
	return (NULL);
}
