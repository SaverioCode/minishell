/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 01:03:46 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/24 22:07:25 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_get_prompt_str(t_info *info)
{
	char	*user_name;
	char	*str;

	str = "\\> ";
	user_name = getenv("USER");
	if (user_name)
	{
		info->prompt = ft_strjoin(user_name, str, 0, 0);
	}
	else
	{
		info->prompt = str;
	}
}

static int	is_empty(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (ft_isprint(str[i]))
			return (1);
		i++;
	}
	return (0);
}

static void	get_input(t_info *info)
{
	char	*str;

	str = NULL;
	while (!str)
	{
		str = readline(info->prompt);
		if (!is_empty(str))
		{	
			free(str);
			str = NULL;
			rl_on_new_line();
		}
	}
	rl_on_new_line();
	if (!info->input)
	{	
		info->input = str;
	}
	else
	{	
		info->input = ft_strjoin(info->input, str, 1, 1);
	}
}

void	ms_handle_input(t_info *info)
{
	int	token;

	token = 0;
	while (token != CHAR)
	{	
		get_input(info);
		token = lexical_check(info->input, token);
		if (token == -1)
		{
			write(2, "Error: incorrect syntax.\n", 25);
			add_history(info->input);
			free(info->input);
			info->input = NULL;
			token = 0;
		}
	}
	add_history(info->input);
}

void	ms_check_input(int ac, char **av)
{
	if (ac > 1)
	{
		write(2, "Error: to many arguments, write only: ./minishell\n", 49);
		exit(0);
	}
	(void)av;
}
