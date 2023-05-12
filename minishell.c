/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:51:46 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/12 05:23:40 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_node		root;
	t_info		info;
	short int	token;

	ft_check_input(ac, av);
	ft_init_shell();
	set_tnode(&root);
	set_starting_env(env, &info);
	// set_signals();
	while (1)
	{
		ft_get_input(&info);
		token = lexical_check(info.input);
		if (token != 0 && token != CHAR)
		{
			if (token == -1)
				free(info.input);
			continue ;
		}
		add_history(info.input);
		ft_parser(&root, info.input);
		// ft_run_all(&root, &info);
	}
	(void)env;
	return (0);
}
