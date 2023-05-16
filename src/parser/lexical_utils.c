/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 04:17:47 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/16 23:04:45 by fgarzi-c         ###   ########.fr       */
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
		if (old != CHAR && old != ')')
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
		if (old_1 == ')' || old_1 == INP || old_1 == HDOC)
			return (-1);
		if (old_1 == OUT || old_1 == APP)
			return (-1);
		if (old_2 == INP || old_1 == HDOC || old_2 == OUT || old_2 == APP)
			return (-1);
		return (0);
	}
	else if (new == ')')
	{
		if (brkts[0] == 0 || old_1 != CHAR)
			return (-1);
		(*brkts)--;
		return (0);
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
	int			status;

	status = token_check_first(new_token, token[0]);
	if (status != -1)
	{	
		status = token_check_second(new_token, token[0], token[1], brkts);
	}
	if (token[0] != new_token)
	{
		token[1] = token[0];
		token[0] = new_token;
	}
	return (status);
}
