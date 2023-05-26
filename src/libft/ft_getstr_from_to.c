/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getstr_from_to.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 00:50:23 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/26 11:29:45 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_getstr_from_to(char *str, int from, int to)
{
	char	*new;
	int		i;

	if (!str || from < 0 || to < 0 || to <= from)
	{	
		return (NULL);
	}
	new = ft_calloc(1, to - from + 2);
	i = 0;
	while (from + i < to + 1)
	{
		new[i] = str[i + from];
		i++;
	}
	return (new);
}
