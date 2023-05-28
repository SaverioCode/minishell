/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_biarrlen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:55:41 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/28 18:38:36 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_biarrlen(char **arr)
{
	size_t	i;

	if (!arr)
	{
		return (0);
	}
	i = 0;
	while (arr[i])
	{
		i++;
	}
	return (i);
}
