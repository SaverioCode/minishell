/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 04:17:47 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/15 19:48:37 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	token_check_first(char old, char new)
{
	if (old == CHAR)
		return (0);
	else if (!old)
	{
		if (new == INP || new == HDOC || new == OUT || new == APP)
			return (0);
		else if (new == CHAR || new == '(')
			return (0);
		return (-1);
	}
	else if (new == '&')
		return (-1);
	else if (old == AND || old == PIPE || old == OR)
	{
		if (new == CHAR || new == '(')
			return (0);
		else if (new == INP || new == HDOC || new == OUT || new == APP)
			return (0);
		return (-1);
	}
	else if (old == INP || old == HDOC || old == OUT || old == APP)
	{
		if (new == CHAR)
			return (0);
		return (-1);
	}
	return (1);
}

static int	token_check_second(char old, char new, int *brkts)
{
	int	status;

	if (old == '(')
	{
		(*brkts)++;
		if (new == CHAR || new == '(')
			return (0);
		else if (new == INP || new == HDOC || new == OUT || new == APP)
			return (0);
		return (-1);
	}
	else if (old == ')')
	{
		if (brkts[0] == 0)
			return (-1);
		(*brkts)--;
		if (new == INP || new == HDOC || new == OUT || new == APP)
			return (0);
		else if (new == AND || new == PIPE || new == ')')
			return (0);
		return (-1);
	}
	return (1);
}

int	token_check_third(int *token, char new)
{
	char	old;
	char	oldest;

	old = token[0];
	oldest = token[1];

}

int	lx_token_check(int *token, char new_token, int *brkts)
{
	static char	old_main_token;
	int			status;

	status = token_check_first(token[0], new_token);
	if (status < 1)
		return (status);
	status = token_check_second(token[0], new_token, brkts);
	if (status < 1)
		return (status);
	status = token_check_third(token, new_token);
	if (status < 1)
		return (status);
	return (-1);
}
