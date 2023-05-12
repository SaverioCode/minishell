/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 01:47:49 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/12 03:22:39 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	which_token(char *str)
{
	if (str[0] == OBRK || str[0] == CBRK)
		return (str[0]);
	else if (str[0] == SQUOTE || str[0] == DQUOTE)
		return (str[0]);
	else if (str[0] == AND1 && str[1] == AND1)
		return (AND);
	else if (str[0] == AND1)
		return (AND1);
	else if (str[0] == INP && str[1] == INP)
		return (INP2);
	else if (str[0] == INP)
		return (INP);
	else if (str[0] == PIPE && str[0] == PIPE)
		return (OR);
	else if (str[0] == PIPE)
		return (PIPE);
	else if (ft_isprint(str[0]))
		return (CHAR);
	return (0);
}


int	lexical_check(t_info *info)
{
	char	token;
	char	new_token;
	size_t	i;

	i = 0;
	token = 0;
	while (info->input[i])
	{
		if (ft_isprint(info->input[i]))
		{
			new_token = which_token(&info->input[i]);
			if (check_token(token, new_token) == -1)
			{
				/// write error indicando il token sbagliato ///
				return (-1);
			}
			token = new_token;
		}
		i++;
	}
	return (token);
}
