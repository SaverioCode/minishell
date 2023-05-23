/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getstr_from_to.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 00:50:23 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/23 23:27:26 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_getstr_from_to(char *str, int from, int to)
{
	char	*new_str;
	int		i;

	if (!str || from < 0 || to < 0 || to <= from)
	{	
		return (NULL);
	}
	new_str = ft_calloc(1, from + to + 1);
	i = 0;
	while (from + i < to + 1)
	{
		new_str[i] = str[i + from];
		i++;
	}
	return (new_str);
}
