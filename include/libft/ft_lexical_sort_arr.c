/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexical_sort_arr.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 23:41:25 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/07/15 23:56:40 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_lexical_sort_arr(char **arr)
{
	char		*tmp;
	__uint32_t	i;
	__uint32_t	j;

	if (arr == NULL)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		j = i;
		while (arr[j])
		{
			if (ft_strcmp(arr[i], arr[j]) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
				i = -1;
				break;
			}
			j++;
		}
		i++;
	}
	return (arr);
}
