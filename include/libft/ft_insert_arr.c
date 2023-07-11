/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert_arr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sav <sav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 11:44:59 by sav               #+#    #+#             */
/*   Updated: 2023/07/10 18:49:53 by sav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_insert_arr(char **arr1, __int32_t i, char **arr2)
{
	char		**new_arr;
	__int32_t	j;
	__int32_t	t;

	if (arr1 == NULL)
		return (arr2);
	if (arr2 == NULL)
		return (arr1);
	new_arr = ft_calloc(ft_biarrlen(arr1) + ft_biarrlen(arr2) + 1, sizeof(char *));
	j = 0;
	while (j < i)
	{
		new_arr[j] = arr1[j];
		j++;
	}
	t = 0;
	while (arr2[t])
	{
		new_arr[j + t] = arr2[t];
		t++; 
	}
	while (arr1[j])
	{
		new_arr[j + t] = arr1[j];
		j++;
	}
	free(arr1);
	free(arr2);
	return (new_arr);
}
