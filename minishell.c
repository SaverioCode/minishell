/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:51:46 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/08 11:13:36 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_node	root;
	t_input	input;

	ft_check_input(ac, av);
	ft_init_shell();
	set_tnode(&root);
	root.token = ROOT;
	while (1)
	{
		input.starting = ft_print_prompt();
		if (!input.starting)
			continue ;
		// just for testing maintaining a clean exit //
		if (input.starting && input.starting[0] == 'q')
		{	
			free(input.starting);
			return (0);
		}
		input.current = input.starting;
		ft_parser(&root, &input);
		// ft_run_all(&root);
	}
	(void)env;
	return (0);
}
