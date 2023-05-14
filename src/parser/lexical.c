/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sav <sav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 01:47:49 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/14 20:25:28 by sav              ###   ########.fr       */
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

static void	reset_params(int *token, int *flag, int *brkts, int *i)
{

}

int	lexical_check(char *input, int flag)
{
	static int		token;
	char			new_token;
	static int		brkts;
	static int		flag[2];
	static size_t	i;

	if (!flag)
	{
		reset_params(token, flag, brkts, i);
	}
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
