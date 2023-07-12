/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_wildcard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 20:49:07 by sav               #+#    #+#             */
/*   Updated: 2023/07/12 04:42:28 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**sub_wildcard(char *str)
{
	__uint32_t		i;
	char			**arr;
	int				flag[2];

	flag[0] = 0;
	arr = NULL;
	i = 0;
	while (str[i])
	{
		lx_check_quotes(flag, str[i]);
		if (flag[0] == 0 && str[i] == '*')
		{
			arr = ps_analyze_string(str, i);
			if (arr != NULL)
			{
				return (arr);
			}
		}
		i++;
	}
	return (arr);
}

char	**ps_wildcard(char *str)
{
	char			**arr;

	if (str == NULL)
	{
		return (NULL);
	}
	arr = NULL;
	arr = sub_wildcard(ft_strcpy(str));
	if (arr == NULL)
	{
		arr = ft_push_str(ft_strcpy(str), arr);
	}
	free(str);
	return (arr);
}
