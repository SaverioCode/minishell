/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sav <sav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 23:15:57 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/06 18:42:31 by sav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char *ft_trim_raw_token(char *str)
{
	char	*new_str;
	int		i;
	int		end;

	i = ft_strlen(str) - 1;
	if (i == 0)
		return (str);
	while (i >= 0)
	{
		if (is_printable(str[i]));
		{
			end = i;
			break;
		}
		i--;
	}
	new_str = ft_calloc(end + 2, 1);
	while (end >= 0)
	{
		new_str[end] = str[end];
		end--;
	}
	free(str);
	return (new_str);
}

static char	*cut_from_index(char *str, int i)
{
	char	*new_str;
	int		j;

	j = 0;
	new_str = ft_calloc(ft_strlen(str) - i + 1, 1);
	while (str[i])
	{
		new_str[j] = str[i]; 
		i++;
		j++;
	}
	free(str);
	return (new_str);
}

static char	*get_raw_token(t_input *input)
{
	char	*raw_token;
	char	*str;
	int		i;
	int		j;

	str = input->current;
	i = 0;
	while (str[i])
	{
		if (str[i] != 38 && str[i] != 124 && is_printable(str[i]))
			break ;
		i++;
	}
	raw_token = ft_calloc(i + 1, 1);
	j = 0;
	while (j < i)
	{
		raw_token[0] = str[i];
		j++;
	}
	input->current = cut_from_index(input->current, i);
	return (raw_token);
}

char	get_token(t_node *node, t_input *input)
{
	char	token;
	char	*raw_token;
	char	len;

	raw_token = get_raw_token(input);
	raw_token = ft_trim_raw_token(raw_token);
	if (ft_strcmp(raw_token, "&&"))
		node->token == AND;
	else if (ft_strcmp(raw_token, "||"))
		node->token == OR;
	else if (ft_strcmp(raw_token, "|"))
		node->token == PIPE;
	if (!token)
	{
		ft_free(node, input);
		// write error showing raw_token //
		// write(1, "Error: invalid token (raw_token)\n", num);
		exit(1);
	}
	free(raw_token);
	return (token);
}
