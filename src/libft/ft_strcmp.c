/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 17:31:19 by sav               #+#    #+#             */
/*   Updated: 2023/05/11 18:31:59 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(char *a, char *b, size_t bytes)
{
	int	i;
	int	len_a;
	int	len_b;

	len_a = ft_strlen(a);
	len_b = ft_strlen(b);
	if (len_a + 1 < bytes || len_b + 1 < bytes)
		return (-1);
	i = 0;
	while (i < bytes)
	{
		if ((int)a[i] != (int)b[i])
			return (0);
	}
	return (1);
}
