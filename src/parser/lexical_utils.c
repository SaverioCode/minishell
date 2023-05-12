/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 04:17:47 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/12 08:20:34 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	token_check_first(char old, char new)
{
	if (old == CHAR)
		return (0);
	if (new == '&')
		return (-1);
	if (old == AND || old == PIPE || old == OR)
	{
		if (new == CHAR || new == '(')
			return (0);
		if (new == INP || new == HDOC || new == OUT || new == APP)
			return (0);
		return (-1);
	}
	if (old == INP || old == HDOC || old == OUT || old == APP)
	{
		if (new == CHAR)
			return (0);
		if (new == INP || new == HDOC || new == OUT || new == APP)
			return (0);
		return (-1);
	}
	return (1);
}

static int	token_check_second(char old, char new, int *brkts)
{
	if (old == '(')
	{
		*brkts++;
		if (new == CHAR)
			return (0);
		if (new == INP || new == HDOC || new == OUT || new == APP)
			return (0);
		return (-1);
	}
	if (old == ')')
	{
		if (brkts[0] == 0)
			return (-1);
		*brkts--;
		if (new == INP || new == HDOC || new == OUT || new == APP)
			return (0);
		if (new == AND || new == PIPE)
			return (0);
		return (-1);
	}
	return (1);
}

int	lx_token_check(char token, char new_token, int *brkts)
{
	int	status;

	status = token_check_first(token, new_token);
	if (status <= 0)
		return (status);
	status = token_check_second(token, new_token, brkts);
	if (status <= 0)
		return (status);
	return (-1);
}
