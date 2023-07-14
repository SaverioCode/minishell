/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_lexical.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 01:47:49 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/07/14 22:49:10 by fgarzi-c         ###   ########.fr       */
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
	else if (str[0] == PIPE && str[1] == PIPE)
		return (OR);
	else if (str[0] == PIPE)
		return (PIPE);
	else if (ft_isprint(str[0]))
		return (CHAR);
	return (0);
}

static void	reset_params(int *token, int *flag, int *brkts, size_t *i)
{
	token[0] = 0;
	token[1] = 0;
	flag[0] = 0;
	flag[1] = 0;
	*brkts = 0;
	*i = 0;
}

static int	lx_exit_status(int *flag, int brkts, char token)
{
	if (flag[0] || brkts)
	{
		return (1);
	}
	if (token == INP || token == HDOC || token == OUT || token == APP)
		return (-1);
	token = CHAR;
	return (token);
}

static int	check_if_fd(char *str, int i)
{
	int	start;

	start = i;
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<')
		{
			return (i);
		}
		if (!ft_isdigit(str[i]))
		{
			break ;
		}
		i++;
	}
	return (start);
}

int	lexical_check(char *input, int reset)
{
	static int		tk[2];
	char			new_token;
	static int		brkts;
	static int		flag[2];
	static size_t	i;

	if (!reset)
		reset_params(tk, flag, &brkts, &i);
	while (input[i])
	{
		lx_check_quotes(flag, input[i]);
		if (!flag[0] && ft_isprint(input[i]))
		{
			i = check_if_fd(input, i);
			new_token = lx_which_token(&input[i]);
			if (lx_token_check(tk, new_token, &brkts) == -1)
				return (-1);
			if (tk[0] == AND || tk[0] == OR || tk[0] == HDOC || tk[0] == APP)
				i++;
		}
		i++;
	}
	return (lx_exit_status(flag, brkts, tk[0]));
}
