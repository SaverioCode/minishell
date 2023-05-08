/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:51:46 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/08 13:44:50 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_node	root;
	t_info	info;

	ft_check_input(ac, av);
	ft_init_shell();
	set_tnode(&root);
	root.token = ROOT;
	while (1)
	{
		info.starting_input = ft_print_prompt();
		if (!info.starting_input)
			continue ;
		// just for testing maintaining a clean exit //
		if (info.starting_input && info.starting_input[0] == 'q')
		{	
			free(info.starting_input);
			return (0);
		}
		info.current_input = info.starting_input;
		if (ft_parser(&root, &info) == -1)
		{
			ft_free(&root, &info);
			continue ;
		}
		// ft_run_all(&root);
	}
	(void)env;
	return (0);
}
