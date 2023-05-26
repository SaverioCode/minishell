/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 12:05:48 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/26 12:09:29 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_path   *create_path_node(t_path *node)
{
    t_path  *new;

    new = calloc(1, sizeof(t_path));
    new->str = NULL;
    new->next = NULL;
    if (node)
    {
        node->next = new;
    }
    return (new);
}

static char	*get_raw_paths(char **env)
{
	int	i;
	int	len;

	i = 0;
	while (env[i])
	{
		len = ft_strlen(env[i]);
		if (len >= 6)
		{
			if (ft_strncmp(env[i], "PATH=/", 6) == 1)
			{
				return (env[i]);
			}
		}
		i++;
	}
	return (NULL);
}

void	get_cmd_paths(t_path *path, char **env, char *cmd)
{
	char	*paths;
	int		i;
	int		start;

	paths = get_raw_paths(env);
	if (!paths)
		return ;
	i = 5;
	start = i;
	while (paths[i])
	{
		if (!paths[i + 1])
		{
			path->str = ft_getstr_from_to(paths, start, i);
			path->str = ft_strjoin(path->str, "/", 1, 0);
			path->str = ft_strjoin(path->str, cmd, 1, 0);
		}
		if (paths[i] == ':')
		{
			path->str = ft_getstr_from_to(paths, start, i - 1);
			path->str = ft_strjoin(path->str, "/", 1, 0);
			path->str = ft_strjoin(path->str, cmd, 1, 0);
			path = create_path_node(path);
			start = i + 1;
		}
		i++;
	}
}
