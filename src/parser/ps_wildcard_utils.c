/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_wildcard_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sav <sav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 00:54:44 by sav               #+#    #+#             */
/*   Updated: 2023/07/10 00:07:02 by sav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static __uint32_t	count_wc_duplicate(char *str)
{
	__uint32_t	i;
	__uint32_t	len;
	int			flag[2];

	flag[0] = 0;
	len = 0;
	i = 0;
	while (str[i])
	{
		lx_check_quotes(flag, str[i]);
		if (flag[0] == 0)
		{
			if (str[i] == '*' && str[i - 1] == '*')
			{
				len++;
			}
		}
		i++;
	}
	return (len);
}

static char	*clean_wc_duplicate(char *str)
{
	char 		*new;
	__uint32_t	i;
	__uint32_t	j;
	__uint32_t	len;
	int			flag[2];

	len = count_wc_duplicate(str);
	if (len == 0)
	{
		return (str);
	}
	flag[0] = 0;
	new = ft_calloc(1, sizeof(char));
	i = 0;
	j = 0;
	while (str[i])
	{
		lx_check_quotes(flag, str[i]);
		if (flag[0] == 0 && str[i] == '*' && str[i - 1] == '*')
		{
			i++;
			continue;
		}
		new[j] = str[i];
		j++;
		i++;
	}
	return (new);
}

static char	*get_after(char *str, __uint32_t i)
{
	__uint32_t	j;
	char		*after;

	j = i + 1;
	if (str[j] == '\0')
	{
		return (NULL);
	}
	after = ft_getstr_from_to(str, j, ft_strlen(str));
	/// cleaning duplicate cause SEGFAULT ///
	after = clean_wc_duplicate(after);
	after = ps_clean_quotes(after);
	return (after);
}

static char	*get_prev(char *str, __uint32_t i)
{
	char		*prev;

	prev = ft_getstr_from_to(str, 0, i - 1);
	if (prev != NULL)
	{
		prev = ps_clean_quotes(prev);
	}
	return (prev);
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

static char	*get_prefix(char *str)
{
	char		*prefix;
	__int32_t	i;

	if (str == NULL)
	{
		return (NULL);
	}
	i = ft_find_char_rev(str, '/');
	prefix = NULL;
	if (i == -1)
	{
		prefix = ft_strcpy(str);
		return (prefix);
	}
	if (str[i + 1] != '\0')
	{
		prefix = ft_getstr_from_to(str, i + 1, ft_strlen(str));
	}
	return (prefix);
}

static char	*get_suffix(char *str)
{
	char		*new;
	__uint32_t	i;

	if (str == NULL)
	{
		return (NULL);
	}
	i = 0;
	new = NULL;
	while (str[i])
	{
		if (str[i] == '/')
		{
			i--;
			break;
		}
		i++;
	}
	new = ft_getstr_from_to(str, 0, i);
	return (new);
}

char	**ps_analyze_string(char *str, __uint32_t i)
{
	char		*prev;
	char		*after;
	char		*dir;
	char		*prefix;
	char		*suffix;
	char		**matrix;

	if (str == NULL)
	{
		return (NULL);
	}
	prev = get_prev(str, i);
	after = get_after(str, i);
	dir = get_dir(prev);
	prefix = get_prefix(prev);
	suffix = get_suffix(after);
	free(after); ///  ????? am I sure??
	free(prev);
	matrix = get_matrix(prefix, suffix, dir);
	if (matrix == NULL)
	{
		matrix = ft_push_str(str, matrix);
		return (matrix);
	}
	return (matrix);
}