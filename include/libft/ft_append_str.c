/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sav <sav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 23:35:02 by sav               #+#    #+#             */
/*   Updated: 2023/07/09 23:56:10 by sav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_append_str(char **arr, char *str)
{
	char		**new_arr;
	__int32_t	len;
	__int32_t	i;

	if (str == NULL)
	{
		return (arr);
	}
	if (arr == NULL)
	{
		new_arr = ft_calloc(2, sizeof(char *));
		new_arr[0] = str;
		return (new_arr);
	}
	len = ft_biarrlen(arr);
	new_arr = ft_calloc(len + 2, sizeof(char *));
	i = 0;
	while (i < len)
	{
		new_arr[i] = arr[i];
		i++;
	}
	new_arr[i] = str;
	free(arr);
	return (new_arr);
}
