/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 22:58:42 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/04 23:01:31 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_numlen(long long num, int base)
{
	int	counter;

	if (base < 2)
		ft_error("Error: number base to low!\n");
	counter = 0;
	if (num < 0)
	{
		num *= -1;
		counter++;
	}
	while (num > 0)
	{	
		num /= base;
		counter++;
	}
	return (counter);
}
