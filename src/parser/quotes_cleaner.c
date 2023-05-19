/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_cleaner.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 18:37:25 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/19 07:03:08 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	count_quotes(int *flag, char c, size_t *len)
{
	if (c == 34 || c == 96)
	{
		if (!flag[0])
		{
			(*len)++;
			flag[0] = 1;
			flag[1] = c;
		}
		else if (flag[1] == c)
		{
			flag[0] = 0;
			flag[1] = 0;
		}
	}
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
	while (str[++i])
		count_quotes(flag, str[i], &len);
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
