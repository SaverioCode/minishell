/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separete_nodes_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:35:46 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/11 20:20:21 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	flag_is_on(int *flag, int *brackets, char c)
{
	if (c == 34 || c == 96)
	{
		if (flag[0] == c)
		{
			flag[0] = 0;
			flag[1] = 0;
		}
	}
	else if (c == 28 && flag[1] == 28)
	{
		*brackets += 1;
	}
	else if (c == 29 && flag[1] == 28)
	{
		*brackets -= 1;
		if (*brackets == 0)
		{
			flag[0] = 0;
			flag[1] = 0;
		}
	}
}

static int	flag_is_off(int *flag, int *brackets, char c)
{
	if (c == 34 || c == 96 || c == 28)
	{
		if (c == 28)
		{	
			*brackets += 1;
		}
		flag[0] = 1;
		flag[1] = c;
	}
	else if (c == 29)
	{
		// write error ')' //
		return (-1);
	}
	return (0);
	
}

int	ft_check_flag(int *flag, char c, int *brackets)
{
	if (c == 34 || c == 96 || c == 28 || c == 29)
	{
		if (flag[0])
		{
			flag_is_on(flag, brackets, c);
		}
		else if (!flag[0])
		{	
			if (flag_is_off(flag, brackets, c) == -1)
			{
				return (-1);
			}
		}
	}
	return (0);
}