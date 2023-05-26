/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 01:12:28 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/26 10:48:32 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(char c)
{
	if ((c > 32 && c < 127) || c > 127)
		return (1);
	return (0);
}

int	ft_find_printable(char *str, char c)
{
	size_t	i;

	i = 0;
	if (c == '+')
	{
		while (str[i])
		{
			if (ft_isprint(str[i]))
				return (i);
			i++;
		}
	}
	else if (c == '-')
	{
		i = ft_strlen(str);
		while (i >= 0)
		{
			if (ft_isprint(str[i]))
				return (i);
			i--;
		}
	}
	return(-1);
}
