/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sav <sav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 01:47:49 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/14 19:17:58 by sav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	lx_which_token(char *str)
{
	if (str[0] == INP && str[1] == INP)
		return (HDOC);
	else if (str[0] == INP)
		return (INP);
	else if (str[0] == OUT && str[1] == OUT)
		return (APP);
	else if (str[0] == OUT)
		return (OUT);
	else if (str[0] == '(' || str[0] == ')')
		return (str[0]);
	else if (str[0] == '&' && str[1] == '&')
		return (AND);
	else if (str[0] == '&')
		return ('&');
	else if (str[0] == PIPE && str[0] == PIPE)
		return (OR);
	else if (str[0] == PIPE)
		return (PIPE);
	else if (ft_isprint(str[0]))
		return (CHAR);
	return (0);
}

void	lx_check_quotes(int *flag, char c)
{
	if (c == 34 || c == 96)
	{
		if (!flag[0])
		{
			flag[0] = 1;
			flag[1] = c;
		}
		else if (flag[1] == c)
		{
			flag[0] = 0;
			flag[1] = 0;
		}
	}
}

int	lexical_check(char *input)
{
	int		token;
	char	new_token;
	int		brkts;
	int		flag[2];
	size_t	i;

	i = 0;
	token = 0;
	flag[0] = 0;
	brkts = 0;
	while (input[i])
	{
		lx_check_quotes(flag, input[i]);
		if (!flag[0] && ft_isprint(input[i]))
		{
			new_token = lx_which_token(&input[i]);
			if (lx_token_check(token, new_token, &brkts) == -1)
			{
				/// write error indicando il token sbagliato ///
				return (-1);
			}
			token = new_token;
		}
		i++;
	}
	if (flag[0] || brkts)
		return (1);
	return (token);
}
