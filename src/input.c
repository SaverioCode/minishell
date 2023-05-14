/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sav <sav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 01:03:46 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/14 19:56:30 by sav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_input(int ac, char **av)
{
	if (ac > 1)
	{
		write(2, "Error: to many arguments, write only: ./minishell\n", 49);
		exit(0);
	}
	(void)av;
}

static int	is_empty(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (is_print(str[i]))
			return (1);
		i++;
	}
	return (0);
}

void	ft_get_input(t_info *info)
{
	char	*user_name;
	char	*str;

	user_name = getenv("USER");
	write(1, user_name, ft_strlen(user_name));
	str = readline("\\> ");
	if (!is_empty(str))
	{	
		free(str);
		// clean buffer //
		ft_get_input(info);
	}
	// clean buffer //
	if (info->input)
		info->input = ft_strjoin(info->input, str);
	else
		info->input = str;
}

