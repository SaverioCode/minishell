/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 23:15:57 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/09 18:33:51 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void cut_token(t_node *node, t_info *info)
{
	int		size;
	char	*str;
	int		len;
	int		i;

	if (node->token == AND || node->token == OR)
		size = 2;
	else if (node->token == PIPE)
		size = 1;
	else if (node->token == END)
		return (info->current_input);
	len = ft_strlen(info->current_input) - size;
	str = ft_calloc(len + 1, 1);
	i = 0;
	while (i < len)
	{
		str[i] = info->current_input[i + size];
		i++;
	}
	free(info->current_input);
	info->current_input = str;
}

int	get_token(t_node *node, t_info *info)
{
	char	token;
	char	*raw_token;
	char	len;

	if (ft_strncmp(info->current_input, "&&", 2))
		node->token == AND;
	else if (ft_strncmp(info->current_input, "&", 1))
		node->token == NULL;
	else if (ft_strncmp(info->current_input, "||", 2))
		node->token == OR;
	else if (ft_strncmp(info->current_input, "|", 1))
		node->token == PIPE;
	else
		node->token == END;
	if (!token)
	{
		ft_free(node, info);
		// write error showing raw_token //
		// write(1, "Error: invalid token (raw_token)\n", num);
		return (-1);
	}
	cut_token(node, info);
	return (0);
}
