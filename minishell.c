/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:51:46 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/01 17:20:33 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_prompt(void)
{
	char	*user_name;

	user_name = getenv("USER");
	printf("\033[38:5:250m%s\\>\n", user_name);
}

int	main(int ac, char **av, char **env)
{
	ft_init_shell();
	// while (1)
	// {
		ft_print_prompt();
	// }
	usleep(1000000);
	return (0);
}
