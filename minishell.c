/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:51:46 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/19 22:31:30 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)

{
	t_node		*root;
	t_info		*info;

	ft_check_input(ac, av);
	root = ft_calloc(1, 8);
	info = ft_calloc(1, 8);
	// init_tnode(root);
	init_tinfo(info);
	// // ft_set_starting_env(env, info);  /// problems here /// but check if delete before correct them ///
	// // write(1, "C\n", 2);////////
	// // set_signals();
	ft_init_shell();
	while (1)
	{
		ft_handle_input(info);
		write(1, "A\n", 2);////////
		// // ft_parser(&root, info.input);
		// // // ft_run_all(&root, &info);
		// ft_free(root, NULL);
		// write(1, "B\n", 2);////////
		// free(info->input);
		// write(1, "C\n", 2);////////
	}
	(void)env;
	// (void)root;
	return (0);
}
