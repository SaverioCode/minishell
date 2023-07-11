/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_arr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sav <sav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 18:48:00 by sav               #+#    #+#             */
/*   Updated: 2023/07/10 20:39:57 by sav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_append_arr(char **arr1, char **arr2)
{
	char		**new;
	__uint32_t	i;
	__uint32_t	j;

	if (arr1 == NULL && arr2 == NULL)
		return (NULL);
	if (arr1 == NULL)
		return (arr2);
	if (arr2 == NULL)
		return (arr1);
	new = ft_calloc(ft_biarrlen(arr1) + ft_biarrlen(arr2) + 1, sizeof(char *));
	i = 0;
	while (arr1 && arr1[i])
	{
		new[i] = arr1[i];
		i++;
	}
	j = 0;
	while (arr2 && arr2[j])
	{
		new[i] = arr2[j];
		j++;
		i++;
	}
	free(arr1);
	free(arr2);
	return (new);
}
