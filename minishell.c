/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:51:46 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/22 11:11:07 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)

{
	t_node		*root;
	t_info		*info;

	ft_check_input(ac, av);
	info = NULL;
	info = ft_calloc(1, sizeof(t_info));
	init_tinfo(info);
	info->env = env;
	// ft_set_starting_env(env, info);  /// problems here /// but check if delete before correct them ///
	// set_signals();
	ft_init_shell();
	while (1)
	{
		root = NULL;
		root = ft_calloc(1, sizeof(t_node));
		init_tnode(root);
		ft_handle_input(info);
		ft_parser(root, info->input);
		// ft_run_all(&root, &info);
		ft_free(root, NULL);
		free(info->input);
	}
	(void)env;
	return (0);
}
