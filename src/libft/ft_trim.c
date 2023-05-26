/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 10:34:12 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/26 11:32:24 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_trim(char *str, char *head)
{
	char	*new;
	int		i;
	int		start;
	int		end;

	if (!str)
	{
		return (NULL);
	}
	start = ft_find_printable(str, '+');
	end = ft_find_printable(str, '-');
	if (start > end || start == -1 || end == -1)
	{
		free(str);
		return (NULL);
	}
	new = ft_calloc(end - start + 2, 1);
	i = 0;
	while (start + i <= end)
	{
		new[i] = str[start + i];
		i++;
	}
	free(head);
	return (new);
}
