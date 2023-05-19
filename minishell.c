/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:51:46 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/19 06:30:54 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_node		root;
	t_info		info;

	ft_check_input(ac, av);
	init_tnode(&root);
	ft_set_env(env, &info);
	// set_signals();
	ft_init_shell();
	while (1)
	{
		ft_handle_input(&info);
		ft_parser(&root, info.input);
		// ft_run_all(&root, &info);
		ft_free(root, NULL);
	}
	return (0);
}
