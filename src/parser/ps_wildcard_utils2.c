/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_wildcard_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sav <sav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 01:42:54 by sav               #+#    #+#             */
/*   Updated: 2023/07/09 23:58:19 by sav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static __int8_t	check_prefix(char *name, char *prefix)
{
	__int32_t	i;

	if (prefix == NULL)
	{
		return (0);
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
	__int32_t	len;

	if (suffix == NULL)
	{
		return (0);
	}
	len = ft_strlen(suffix) - 1;
	i = 0;
	while (suffix[len])
	{
		if (suffix[len] != name[len_name - 1 - i])
		{
			return (-1);
		}
		len--;
		i++;
	}
	return (0);
}

static __int8_t	check_name(char *name, char *prefix, char *suffix)
{
	__int32_t	len_name;
	__int32_t	len;

	if (name[0] == '.')
	{
		return (-1);
	}
	if (prefix == NULL && suffix == NULL)
	{
		return (0);
	}
	len_name = ft_strlen(name);
	len = ft_strlen(prefix) + ft_strlen(suffix);
	if (len > len_name)
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

static char	*get_wildcard_value(char *str, char *prefix, char *suffix)
{
	char		*new;
	__int32_t	start;
	__int32_t	end;

	start = ft_strlen(prefix) - 1;
	if (start == -1)
	{
		start = 0;
	}
	if (ft_strlen(suffix) == 0)
	{
		end = ft_strlen(str) - 1;
	}
	else
	{
		end = ft_strlen(str) - ft_strlen(suffix) - 1;
	}
	new = ft_calloc(start + end + 1, sizeof(char));
	new = ft_getstr_from_to(str, start, end);
	return (new);
}

char	**get_matrix(char *prefix, char *suffix, char *dir)
{
	DIR				*dir_stream;
	struct dirent	*dir_node;
	char			*name;
	char			**matrix;

	matrix = NULL;
	dir_stream = opendir(dir);
	dir_node = readdir(dir_stream);
	while (dir_node)
	{
		if (check_name(dir_node->d_name, prefix, suffix) == 0)
		{
			name = get_wildcard_value(dir_node->d_name, prefix, suffix);
			printf("GETM|%s|\n", name);//////
			matrix = ft_append_str(matrix, name);
		}
		dir_node = readdir(dir_stream);
	}
	write(1, "END\n", 4);/////////////////////////
	/// I need to alphabeticaly order the array ///
	closedir(dir_stream);
	return (matrix);
}
