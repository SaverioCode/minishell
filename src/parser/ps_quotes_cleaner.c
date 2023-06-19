/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_quotes_cleaner.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 18:37:25 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/06/20 01:29:07 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_quotes(char *str)
{
	int	i;
	int	len;
	int	flag;

	flag = 0;
	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			if (!flag)
			{
				len++;
				flag = str[i];
			}
			else if (flag == str[i])
			{
				len++;
				flag = 0;
			}
		}
		i++;
	}
	return (len);
}

char	*ps_quotes_cleaner(char *str)
{
	char	*new_str;
	size_t	i;
	size_t	len;
	size_t	j;
	int		flag[2];

	flag[0] = 0;
	len = 0;
	i = -1;
	len = count_quotes(str);
	if (!len)
		return (str);
	new_str = ft_calloc(1, ft_strlen(str) - len + 1);
	i = 0;
	j = -1;
	while (str[i])
	{
		lx_check_quotes(flag, str[i]);
		if (flag[0] && flag[1] == str[i])
			new_str[++j] = str[i];
		i++;
	}
	free(str);
	return (new_str);
}
