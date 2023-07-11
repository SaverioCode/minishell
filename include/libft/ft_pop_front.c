/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pop_front.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sav <sav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 19:04:28 by sav               #+#    #+#             */
/*   Updated: 2023/07/10 20:19:01 by sav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char **ft_pop_front(char **arr)
{
	char		**new;
	__uint32_t	i;
	__uint32_t	len;

	if (arr == NULL)
	{
		return (NULL);
	}
	len = ft_biarrlen(arr);
	if (len == 1)
	{
		// free(arr[0]);
		free(arr);
		return (NULL);
	}
	new = ft_calloc(len, sizeof(char *));
	i = 0;
	while (arr[i + 1])
	{
		new[i] = arr[i + 1];
		i++;
	}
	// free(arr[0]);
	free(arr);
	return (new);
}
