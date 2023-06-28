/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_wildcard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sav <sav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 20:49:07 by sav               #+#    #+#             */
/*   Updated: 2023/06/28 20:23:53 by sav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ps_wildcard(char *str)
{
	__uint32_t		i;
	int				flag[2];

	flag[0] = 0;
	i = 0;
	while (str[i])
	{
		lx_check_quotes(flag, str[i]);
		if (flag[0] == 0 && str[i] == '*')
		{
			str = ms_sub_wildcard(str, i);
			i = -1;
		}
		i++;
	}
	return (str);
}
