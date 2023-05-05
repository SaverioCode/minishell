/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 23:15:57 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/05 00:14:38 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	check_flag(int *flag, char c)
{
	if (c == 34 || c == 96 || c == 28 || c == 29)
	{
		if (flag[0])
		{	
			if ((flag[1] == 28 && c == 29) || (flag[1] != 28 && c == flag[1]))
			{
				flag[0] = 0;
				flag[1] = 0;
			}
		}
		else if (!flag[0] && c != 29)
		{
			flag[0] = 1;
			flag[1] = c;
		}
	}
}

// static int	is_token(int *flag, char c)
// {
// 	if (!flag[0])
// 	{
// 		if (c == 26 || c = 124)
// 	}
// }

static char	*split_input(t_exps *exp, char *input, int end)
{
	char	*str;
	char	*expression;
	char	i;
	char	len;

	exp = ft_calloc(i, 1);
	i = 0;
	while (i < end)
	{
		expression[i] = input[i];
		i++;
	}
	exp->exp = expression;
	free(input);
	return (str);
}

void	ft_separete_exps(t_exps *exp, char *input)
{
	int	i;
	int	flag[2];

	flag[0] = 0;
	i = 0;
	while (input[i])
	{
		check_flag(flag, input[i]);
		if (!flag[0] && (input[i] == 26 || input[i] == 124))
		{
			input = split_input(input, i);
			i = -1;
		}
		i++;
	}
	if (flag[0])
	{
		write(2, "Error: quotes or parentesi\n", 27);
		// friare tutto //
		exit(1);
	}
}
