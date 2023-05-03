/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 01:03:46 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/04 01:29:50 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_input(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] > 32 && str[i] < 127)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_print_prompt(void)
{
	char	*user_name;
	char	*str;

	user_name = getenv("USER");
	write(1, user_name, ft_strlen(user_name));
	str = readline("\\> ");
	if (check_input(str))
		add_history(str);
	return (str);
}
