/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_wildcard_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 01:42:54 by sav               #+#    #+#             */
/*   Updated: 2023/07/13 22:22:30 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static __int8_t	check_invalid_options(char *name, char *str)
{
	__uint32_t	len_name;
	__uint32_t	len_str;

	if (name[0] == '.' && str[0] != '.')
		return (-1);
	if (str[0] != 6 && (name[0] != str[0]))
		return (-1);
	len_name = ft_strlen(name) - 1;
	len_str = ft_strlen(str) - 1;
	if (str[len_str] != 6 && name[len_name] != str[len_str])
		return (-1);
	return (0);
}

static __int8_t	check_name(char *name, char *str)
{
	__int32_t	i;
	__int32_t	j;

	if (check_invalid_options(name, str) == -1)
		return (-1);
	if (ft_strlen(str) == 1 && str[0] == 6)
		return (0);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == 6)
		{
			if (str[i + 1] == 0)
				return (0);
			if (ft_find_char(&name[j], str[i + 1]) == -1)
				return (-1);
			j += ft_find_char(&name[j], str[i + 1]);
			i++;
		}
		else if (str[i] != name[j])
			return (-1);
		i++;
		j++;
	}
	return (0);
}

char	**ps_get_matrix(char *dir, char *str)
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
		if (check_name(dir_node->d_name, str) == 0)
		{
			name = ft_strcpy(dir_node->d_name);
			matrix = ft_append_str(matrix, name);
		}
		dir_node = readdir(dir_stream);
	}
	/// I need to alphabeticaly order the array   ///
	/// this problem seems not to occure on MacOS ///
	closedir(dir_stream);
	return (matrix);
}
