/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_arr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sav <sav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 18:48:00 by sav               #+#    #+#             */
/*   Updated: 2023/06/30 19:20:04 by sav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_append_arr(char **arr1, char **arr2)
{
	char		**new;
	__uint32_t	i;
	__uint32_t	j;
	__uint32_t	len1;
	__uint32_t	len2;

	len1 = ft_biarrlen(arr1);
	len2 = ft_biarrlen(arr2);
	if (len1 + len2 == 0)
	{
		return (NULL);
	}
	new = ft_calloc(len1 + len2 + 1, sizeof(char *));
	i = 0;
	while (arr1 && arr1[i])
	{
		new[i] = arr1[i];
		i++;
	}
	j = 0;
	while (arr2 && arr2[2])
	{
		new[i] = arr2[j];
		j++;
		i++;
	}
	return (new);
}
