/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 18:50:25 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/01 17:23:33 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long	num;
	int		i;
	char	sign;

	if (!str)
		return (0);
	i = 0;
	while (str[i] == 32 || str[i] == 9 || (str[i] >= 11 && str[i] <= 13))
		i++;
	if (str[i] == 43 || str[i] == 45)
		sign = str[i++];
	num = 0;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			return (0);
		else if (str[i] > 47 && str[i] < 58)
			num = (num * 10) + ((int)str[i] - 48);
		i++;
	}
	if (sign && sign == 45)
		num *= -1;
	if (num > INT_MAX || num < INT_MIN)
		return (0);
	return (num);
}
