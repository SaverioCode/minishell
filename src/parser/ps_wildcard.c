/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_wildcard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sav <sav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 20:49:07 by sav               #+#    #+#             */
/*   Updated: 2023/07/07 15:00:20 by sav              ###   ########.fr       */
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
	arr = ft_push_str(str, arr);
	return (arr);
}

char	**ps_wildcard(char *str)
{
	__uint32_t		i;
	char			**arr;
	char			**new_arr;

	arr = sub_wildcard(str);
	i = 0;
	if (arr != NULL)
	{
		while (arr[i])
		{
			new_arr = sub_wildcard(arr[i]);
			arr = ft_rm_str_from_arr(arr, i);
			if (new_arr != NULL)
			{
				arr = ft_append_arr(arr, new_arr);
				continue ;
			}
			i++;
		}
	}
	return (arr);
}
