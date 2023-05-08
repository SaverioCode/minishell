/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 23:15:57 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/08 17:00:15 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*cut_nbytes(t_info *info, int size)
{
	char	*new_str;
	char	*str;
	char	*raw_token;
	int		i;

	if (!size)
		return (0);
	str = info->current_input;
	i = 0;
	new_str = ft_calloc(ft_strlen(str) - size, 1);
	raw_token = ft_calloc(size + 1, 1);
	while (i < size)
	{
		raw_token[i] = str[i];
		i++;
	}
	while (str[i])
	{
		new_str[i - size] = str[i]; 
		i++;
	}
	free(info->current_input);
	info->current_input = new_str;
	return (raw_token);
}

static char	*get_raw_token(t_info *info)
{
	char	*raw_token;
	char	*str;
	int		i;
	char	size;

	size = 0;
	str = info->current_input;
	i = 0;
	if (str[i] == 38 && str[i] != 38)
		size = 1;
	else if (str[i] == 124 && str[i] != 124)
		size = 1;
	else if (str[i] == 124 && str[i] == 124 && str[i] != 124)
		size = 2;
	raw_token = cut_nbytes(info, size);
	return (raw_token);
}

int	get_token(t_node *node, t_info *info)
{
	char	token;
	char	*raw_token;
	char	len;

	raw_token = get_raw_token(info);
	if (check_current_input(info) == -1)
		token = NULL;
	if (ft_strcmp(raw_token, "&&"))
		node->token == AND;
	else if (ft_strcmp(raw_token, "||"))
		node->token == OR;
	else if (ft_strcmp(raw_token, "|"))
		node->token == PIPE;
	if (!token)
	{
		ft_free(node, info);
		// write error showing raw_token //
		// write(1, "Error: invalid token (raw_token)\n", num);
		free(raw_token);
		return (-1);
	}
	free(raw_token);
	return (0);
}
