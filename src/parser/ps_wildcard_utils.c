/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_wildcard_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 00:54:44 by sav               #+#    #+#             */
/*   Updated: 2023/07/13 22:25:14 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static __uint32_t	get_len(char *str)
{
	__uint32_t	i;
	__uint32_t	starting_len;
	__uint32_t	len;

	starting_len = ft_strlen(str);
	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == 6)
		{
			while (str[i + 1] == 6)
			{
				i++;
			}
		}
		len++;
		i++;
	}
	if (starting_len == len)
		return (0);
	return (len);
}

static char	*clean_wc_duplicate(char *str)
{
	char		*new;
	__uint32_t	i;
	__uint32_t	j;
	__uint32_t	len;

	len = get_len(str);
	if (len == 0)
		return (str);
	new = ft_calloc(len + 1, sizeof(char));
	i = 0;
	j = 0;
	while (str[i])
	{
		new[j] = str[i];
		if (str[i] == 6)
		{
			while (str[i + 1] == 6)
				i++;
		}
		j++;
		i++;
	}
	free(str);
	return (new);
}

static char	*get_dir(char *str)
{
	char		*dir;
	__int32_t	i;

	i = ft_find_char_rev(str, '/');
	dir = NULL;
	if (i == -1)
	{
		dir = bi_get_cwd();
		return (dir);
	}
	dir = ft_getstr_from_to(str, 0, i);
	return (dir);
}

char	**ps_analyze_string(char *str)
{
	char		*dir;
	char		**matrix;

	if (str == NULL)
	{
		return (NULL);
	}
	str = ps_clean_quotes(str);
	str = clean_wc_duplicate(str);
	dir = get_dir(NULL);
	matrix = ps_get_matrix(dir, str);
	free(str);
	free(dir);
	return (matrix);
}
