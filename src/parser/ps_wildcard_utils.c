/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_wildcard_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sav <sav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 00:54:44 by sav               #+#    #+#             */
/*   Updated: 2023/06/28 22:59:28 by sav              ###   ########.fr       */
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

static char	*clean_wd_duplicate(char *str)
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
	after = clean_wc_duplicate(after);
	after = ps_quotes_cleaner(after);
	return (after);
}

static char	*get_prev(char *str, __uint32_t i)
{
	char		*prev;

	prev = ft_getstr_from_to(str, 0, i);
	prev = ps_quotes_cleaner(prev);
	return (prev);
}

static char	*get_dir(char *str)
{
	char		*dir;
	__uint32_t	i;

	i = ft_find_char_rev(str, '/');
	dir = NULL;
	if (i == -1)
	{
		dir == bi_get_cwd();
		return (dir);
	}
	dir = ft_getstr_from_to(str, 0, i);
	return (dir);
}

static char	*get_prefix(char *str)
{
	char		*prefix;
	__uint32_t	i;

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

static __int8_t	check_prefix(char *name, char *prefix)
{
	__int32_t	i;

	if (prefix == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (prefix[i])
	{
		if (prefix[i] != name[i])
		{
			return (-1);
		}
		i++;
	}
	return (0);
}

static __int8_t	check_suffix(char *name, __int32_t len_name, char *suffix)
{
	__int32_t	i;

	if (suffix == NULL)
	{
		return (0);
	}
	i = 0;
	while (suffix[i])
	{
		if (suffix[i] != name[len_name - 1 - i])
		{
			return (-1);
		}
		i++;
	}
	return (0);
}

static __int8_t	check_name(char *name, char *prefix, char *suffix)
{
	__int32_t	len_name;
	__int32_t	len;

	if (prefix == NULL && suffix == NULL)
	{
		return (0);
	}
	len_name = ft_strlen(name);
	len = ft_strlen(prefix) + ft_strlen(suffix);
	if (len_name > len);
	{
		return (-1);
	}
	if (check_prefix(name, prefix) == -1)
	{
		return (-1);
	}
	if (check_suffix(name, len_name, suffix) == -1)
	{
		return (-1);
	}
	return (0);
}

static char	**get_matrix(char *prefix, char *suffix, char *dir)
{
	DIR				*dir_stream;
	struct dirent	*dir_node;
	char			*name;
	char			**matrix;

	matrix == NULL;
	dir_stream = opendir(dir);
	dir_node = readdir(dir);
	while (dir_node)
	{
		name = ft_strcpy(dir_node->d_name);
		if (check_name(name, prefix, suffix) == 0)
		{
			matrix = ft_push_matrix();  // or push_arr() // both missing
		}
		free(name);
		dir_node = readdir(dir);
	}
	closedir(dir);
	return (matrix);
}

static char	**analyze_string(char *str, __uint32_t i)
{
	char		*prev;
	char		*after;
	char		*dir;
	char		*prefix;
	char		*suffix;

	if (str == NULL)
	{
		return (NULL);
	}
	prev = get_prev(str,  i);
	after = get_after(str, i);
	dir = get_di(prev);
	prefix = get_prefix(prev);
	suffix = get_suffix(after);
	free(after);
	free(prev);
	/// matrix == get_matrix(prefix, suffix, dir);
	/// if (matrix == NULL)
	///	{
	///		return (str???);
	///	}
	return (get_matrix(prefix, suffix, dir));
}