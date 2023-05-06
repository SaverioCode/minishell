/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:51:46 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/04 01:35:19 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_node	root;
	char	*input;

	ft_check_input(ac, av);
	ft_init_shell();
	root.token = ROOT;
	while (1)
	{
		input = ft_print_prompt();
		if (!input)
			continue ;
		// just for testing maintaining a clean exit //
		if (input && input[0] == 'q')
		{	
			free(input);
			return (0);
		}
		ft_parser(&root, input);
		free(input);
	}
	(void)env;
	return (0);
}
