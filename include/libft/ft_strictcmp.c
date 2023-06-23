/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strictcmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:51:23 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/06/23 16:18:53 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strictcmp(char *str1, char *str2)
{
	int	i;

	if (ft_strlen(str1) != ft_strlen(str2))
	{
		return (-1);
	}
	i = 0;
	while (str1[i])
	{
		if ((unsigned char)str1[i] != (unsigned char)str2[i])
		{
			return (-1);
		}
		i++;
	}
	return (0);	
}
