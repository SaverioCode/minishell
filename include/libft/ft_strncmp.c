/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 17:31:19 by sav               #+#    #+#             */
/*   Updated: 2023/06/14 22:03:35 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(char *a, char *b, size_t bytes)
{
	size_t	i;
	size_t	len_a;
	size_t	len_b;

	len_a = ft_strlen(a);
	len_b = ft_strlen(b);
	if (!a || !b || len_a < bytes || len_b < bytes)
	{
		return (-1);
	}
	i = 0;
	while (i < bytes)
	{
		if ((int)a[i] != (int)b[i])
		{
			return (0);
		}
		i++;
	}
	return (1);
}
