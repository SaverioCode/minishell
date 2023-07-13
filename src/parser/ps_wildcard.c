/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_wildcard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 20:49:07 by sav               #+#    #+#             */
/*   Updated: 2023/07/13 18:28:32 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*convert_wildcard(char *str)
{
	__uint32_t		i;
	int				flag[2];

	flag[0] = 0;
	i = 0;
	while (str[i])
	{
		lx_check_quotes(flag, str[i]);
		if (flag[0] == 0 && str[i] == '*')
		{
			str[i] = 6;
		}
		i++;
	}
	return (str);
}

char	**ps_wildcard(char *str)
{
	char	*converted;
	char	**arr;

	if (str == NULL)
	{
		return (NULL);
	}
	arr = NULL;
	converted = convert_wildcard(ft_strcpy(str));
	if (ft_find_char(converted, 6) != -1)
	{
		arr = ps_analyze_string(converted);
	}
	else
	{
		free(converted);
	}
	if (arr == NULL)
	{
		arr = ft_append_str(arr, str);
	}
	return (arr);
}
