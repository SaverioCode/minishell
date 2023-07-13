/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 22:26:13 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/07/13 22:33:30 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	ps_get_token(char *input)
{
	if (input[0] == '&' && input[1] == '&')
	{
		input[0] = 32;
		input[1] = 32;
		return (AND);
	}
	else if (input[0] == '|' && input[1] == '|')
	{
		input[0] = 32;
		input[1] = 32;
		return (OR);
	}
	else if (input[0] == '|')
	{
		input[0] = 32;
		return (PIPE);
	}
	return (0);
}
