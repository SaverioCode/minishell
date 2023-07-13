/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_wildcard_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sav <sav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 01:42:54 by sav               #+#    #+#             */
/*   Updated: 2023/07/13 02:42:32 by sav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static __int8_t	check_prefix(char *name, char *prefix)
// {
// 	__int32_t	i;

// 	if (prefix == NULL)
// 	{
// 		return (0);
// 	}
// 	i = 0;
// 	while (prefix[i])
// 	{
// 		if (prefix[i] != name[i])
// 		{
// 			return (-1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// static __int8_t	check_suffix(char *name, __int32_t len_name, char *suffix)
// {
// 	__int32_t	i;
// 	__int32_t	len;

// 	if (suffix == NULL)
// 	{
// 		return (0);
// 	}
// 	len = ft_strlen(suffix) - 1;
// 	i = 0;
// 	while (suffix[len])
// 	{
// 		if (suffix[len] != name[len_name - 1 - i])
// 		{
// 			return (-1);
// 		}
// 		len--;
// 		i++;
// 	}
// 	return (0);
// }

static __int8_t	check_name(char *name, char *str)//char *prefix, char *suffix)
{
	__uint32_t	i;
	__int32_t	j;

	j = 0;
	i = 0;
	if (name[0] == '.' && str[0] != '.')
		return (-1);
	if (ft_strlen(str) == 1 && str[0] == 6)
		return (0);
	while (str[i])
	{
		if (str[i] != 6)
		{
			if (str[i] != name[j])
			{
				return (-1);
			}
		}
		if (str[i] == 6)
		{
			j = ft_find_char(&name[j], str[i + 1]);
			if (j == -1)
			{
				return (-1);
			}
			j--;
		}
		j++;
		i++;
	}
	return (0);
	// __int32_t	len_name;
	// __int32_t	len;

	// if (name[0] == '.')
	// {
	// 	return (-1);
	// }
	// if (prefix == NULL && suffix == NULL)
	// {
	// 	return (0);
	// }
	// len_name = ft_strlen(name);
	// len = ft_strlen(prefix) + ft_strlen(suffix);
	// if (len > len_name)
	// {
	// 	return (-1);
	// }
	// if (check_prefix(name, prefix) == -1)
	// {
	// 	return (-1);
	// }
	// if (check_suffix(name, len_name, suffix) == -1)
	// {
	// 	return (-1);
	// }
	// return (0);
}

// static char	*get_wildcard_value(char *str, char *prefix, char *suffix)
// {
// 	char		*new;
// 	__int32_t	len;
// 	__int32_t	len_prefix;
// 	__int32_t	len_suffix;

// 	len_prefix =  ft_strlen(prefix);
// 	len_suffix = ft_strlen(suffix);
// 	len = ft_strlen(str) - len_prefix - len_suffix;
// 	new = ft_calloc(len + 1, sizeof(char));
// 	new = ft_getstr_from_to(str, len_prefix, len - 1);
// 	return (new);
// }

char	**ps_get_matrix(t_wildcard *info, char *str)
{
	DIR				*dir_stream;
	struct dirent	*dir_node;
	char			*name;
	char			**matrix;

	matrix = NULL;

	dir_stream = opendir(info->dir);
	dir_node = readdir(dir_stream);
	while (dir_node)
	{
		// write(1, "GM0\n", 4);//////////////////
		if (check_name(dir_node->d_name, str) == 0)
		{
			// write(1, "GM1\n", 4);//////////////////
			name = ft_strcpy(dir_node->d_name);
			matrix = ft_append_str(matrix, name);
		}
		// if (check_name(dir_node->d_name, info->prefix, info->suffix) == 0)
		// {
		// 	name = get_wildcard_value(dir_node->d_name, info->prefix, info->suffix);
		// 	name = ft_strjoin(info->prev, name, 0, 0);
		// 	name = ft_strjoin(name, info->after, 0, 0);
		// 	matrix = ft_append_str(matrix, name);
		// }
		dir_node = readdir(dir_stream);
	}
	/// I need to alphabeticaly order the array   ///
	/// this problem seems not to occure on MacOS ///
	closedir(dir_stream);
	return (matrix);
}
