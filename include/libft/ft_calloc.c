/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:21:56 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/26 10:15:05 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t bytes, size_t size)
{
	char	*var;
	int		len;
	int		i;

	len = bytes * size;
	if (len > 16711568)
	{
		ft_error("Error: allocation is to big!\n");
	}
	var = malloc(len);
	if (!var)
	{
		ft_error("Error: allocation failed!\n");
	}
	i = 0;
	while (i < len)
	{
		var[i] = 0;
		i++;
	}
	return (var);
}
