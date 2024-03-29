/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sav <sav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 22:39:01 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/06/28 01:03:14 by sav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_find_char_rev(char *str, char c)
{
	int	i;

	if (str == NULL)
	{
		return (-1);
	}
	i = ft_strlen(str);
	while (i >= 0)
	{
		if (str[i] == c)
		{
			return (i);
		}
		i--;
	}
	return (-1);
}

int	ft_find_char(char *str, char c)
{
	int	i;

	if (str == NULL)
	{
		return (-1);
	}
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			return (i);
		}
		i++;
	}
	return (-1);
}
