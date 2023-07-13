/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_quotes_cleaner.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 18:37:25 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/07/13 19:02:21 by fgarzi-c         ###   ########.fr       */
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

static int	check_quotes(int *flag, char c)
{
	if (c == 34 || c == 39)
	{
		if (*flag == 0)
		{
			*flag = c;
			return (1);
		}
		if (*flag == c)
		{
			*flag = 0;
			return (1);
		}
	}
	return (0);
}

char	*ps_clean_quotes(char *str)
{
	char	*new_str;
	size_t	i;
	size_t	len;
	size_t	j;
	int		flag;

	flag = 0;
	len = count_quotes(str);
	if (!len)
		return (str);
	new_str = ft_calloc(1, ft_strlen(str) - len + 1);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (check_quotes(&flag, str[i]) == 0)
		{
			new_str[j] = str[i];
			j++;
		}
		i++;
	}
	free(str);
	return (new_str);
}

char	**ps_quotes_cleaner(char **arr)
{
	size_t	i;

	if (arr == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (arr[i])
	{
		arr[i] = ps_clean_quotes(arr[i]);
		i++;
	}
	return (arr);
}
