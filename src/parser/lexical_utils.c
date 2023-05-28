/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 04:17:47 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/28 19:46:49 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	token_check_first(char new, char old)
{
	if (new == CHAR)
	{
		if (old == ')')
			return (-1);
		return (0);
	}
	else if (new == '&')
	{	
		return (-1);
	}
	else if (new == AND || new == PIPE || new == OR)
	{
		if (old != CHAR && old != '(' && old != ')')
			return (-1);
		return (0);
	}
	else if (new == INP || new == HDOC || new == OUT || new == APP)
	{
		if (old == INP || old == HDOC || old == OUT || old == APP)
			return (-1);
		return (0);
	}
	return (1);
}

static int	token_check_second(char new, char old_1, char old_2, int *brkts)
{
	if (new == '(')
	{
		(*brkts)++;
		if (old_1 == CHAR)
		{
			if (old_2 != INP && old_2 != HDOC && old_2 != OUT && old_2 != APP)
				return (-1);
			return (0);
		}
		if (old_1 == AND || old_1 == OR || old_1 == PIPE)
		{
			if (old_2 != CHAR)
				return (-1);
			return (0);
		}
		if (old_1 == ')' || old_1 == INP || old_1 == HDOC)
			return (-1);
		if (old_1 == OUT || old_1 == APP)
			return (-1);
		if (old_2 == INP || old_2 == HDOC || old_2 == OUT || old_2 == APP)
			return (-1);
		return (0);
	}
}

static int	token_check_third(char new, char old, int *brkts)
{
	if (new == ')')
	{
		if (brkts[0] == 0 || (old != CHAR && old != ')'))
		{
			return (-1);
		}
		(*brkts)--;
		return (0);
	}
	return (1);
}

int	lx_token_check(int *token, char new_token, int *brkts)
{
	int			status;

	status = token_check_first(new_token, token[0]);
	if (status == 1)
	{	
		status = token_check_second(new_token, token[0], token[1], brkts);
	}
	if (status == 1)
	{
		status = token_check_third(new_token, token[0], brkts);
	}
	if (token[0] != new_token)
	{
		token[1] = token[0];
		token[0] = new_token;
	}
	return (status);
}
