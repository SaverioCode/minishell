/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sav <sav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 17:31:19 by sav               #+#    #+#             */
/*   Updated: 2023/05/06 17:37:57 by sav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char *a, char *b)
{
	int	i;

	if (ft_strlen(a) != ft_strlen(b))
		return (0);
	i = 0;
	while (a[i] && b[i])
	{
		if ((int)a[i] != (int)b[i])
			return (0);
	}
	return (1);
}