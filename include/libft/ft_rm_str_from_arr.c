/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rm_str_from_arr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sav <sav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 19:04:28 by sav               #+#    #+#             */
/*   Updated: 2023/07/07 14:57:23 by sav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char **ft_rm_str_from_arr(char **arr ,__uint32_t index)
{
	char		**new;
	__uint32_t	i;
	__uint32_t	j;
	__uint32_t	len;

	if (arr == NULL)
	{
		return (NULL);
	}
	len = ft_biarrlen(arr);
	if (len == 1)
	{
		free(arr[0]);
		free(arr);
		return (NULL);
	}
	new = ft_calloc(len, sizeof(char *));
	j = 0;
	i = 0;
	while (arr[i])
	{
		if (i == index)
		{
			i++;
		}
		new[i] = arr[j];
		j++;
		i++;
	}
	free(arr[j]);
	free(arr);
	return (new);
}
