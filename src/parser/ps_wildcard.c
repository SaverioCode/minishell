/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_wildcard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sav <sav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 20:49:07 by sav               #+#    #+#             */
/*   Updated: 2023/07/13 02:29:03 by sav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	**sub_wildcard(char *str)
// {
// 	__uint32_t		i;
// 	char			**arr;
// 	int				flag[2];

// 	flag[0] = 0;
// 	arr = NULL;
// 	i = 0;
// 	while (str[i])
// 	{
// 		lx_check_quotes(flag, str[i]);
// 		if (flag[0] == 0 && str[i] == '*')
// 		{
// 			arr = ps_analyze_string(str, i);
// 			if (arr != NULL)
// 			{
// 				return (arr);
// 			}
// 		}
// 		i++;
// 	}
// 	return (arr);
// }

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
		arr = ft_append_str(arr, str);
		return (arr);
	}
	return (arr);
}

// char	**ps_wildcard(char *str)
// {
// 	char			**arr;

// 	if (str == NULL)
// 	{
// 		return (NULL);
// 	}
// 	arr = NULL;
// 	arr = sub_wildcard(str);
// 	if (arr == NULL)
// 	{
// 		arr = ft_push_str(ft_strcpy(str), arr);
// 	}
// 	free(str);
// 	return (arr);
// }
