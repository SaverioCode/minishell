/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sav <sav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 19:48:13 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/06/30 22:49:58 by sav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_push_str(char *str, char **arr)
{
	char	**new;
	int		len;
	int		i;

	len = ft_biarrlen(arr);
	if (!len)
	{
		new = ft_calloc(3, sizeof(char *));
		new[0] = ft_strcpy(str);
		return (new);
	}
	new = ft_calloc(len + 2, 8);
	new[0] = ft_strcpy(str);
	i = 0;
	while (arr[i])
	{
		new[1 + i] = arr[i];
		i++;
	}
	free(arr);
	return (new);
}
