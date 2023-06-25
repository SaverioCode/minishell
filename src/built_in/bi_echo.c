/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sav <sav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 20:53:04 by sav               #+#    #+#             */
/*   Updated: 2023/06/25 21:15:02 by sav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_flag(char *str)
{
	__int32_t	i;

	if (str[0] != '-')
	{
		write(1, str, ft_strlen(str));
		write(1, " ", 1);
		return (1);
	}
	else
	{
		i = 1;
		while (str[i])
		{
			if (str[i] != 'n')
			{
				write(1, str, ft_strlen(str));
				write(1, " ", 1);
				return (1);
			}
			i++;
		}
	}
	return (0);
}

__int8_t	bi_echo(char **args)
{
	__int32_t	i;
	__int8_t	flag;

	if (args == NULL)
	{
		write(1, "\n", 1);
		return (0);
	}
	i = 0;
	flag = check_flag(args[i]);
	i++;
	while (args[i])
	{
		write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1] != NULL)
		{
			write(1, " ", 1);
		}
		i++;
	}
	if (flag == 1)
	{
		write(1, "\n", 1);
	}
	return (0);
}
