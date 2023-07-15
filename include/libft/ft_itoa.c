/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:22:14 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/07/15 23:34:43 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(long num)
{
	int		strlen;
	char	*strnum;

	if (num < INT_MIN || num > INT_MAX)
		return (NULL);
	if (num == 0)
	{
		strnum = ft_calloc(2, sizeof(char));
		strnum[0] = '0';
		return (strnum);
	}
	strlen = ft_numlen(num, 10);
	strnum = ft_calloc(strlen + 1, sizeof(char));
	if (num < 0)
	{
		strnum[0] = 45;
		num *= -1;
	}
	while (num > 0)
	{
		strlen--;
		strnum[strlen] = (num % 10) + 48;
		num /= 10;
	}
	return (strnum);
}
