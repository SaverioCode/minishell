/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:51:46 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/22 11:09:07 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)

{
	t_node		*root;
	t_info		*info;

	ft_check_input(ac, av);
	// ft_set_starting_env(env, info);  /// problems here /// but check if delete before correct them ///
	// set_signals();
	ft_init_shell();
	while (1)
	{
		root = NULL;
		info = NULL;
		root = ft_calloc(1, sizeof(t_node));
		info = ft_calloc(1, sizeof(t_info));
		init_tnode(root);
		init_tinfo(info);
		ft_handle_input(info);
		ft_parser(root, info->input);
		// ft_run_all(&root, &info);
		ft_free(root, NULL);
		free(info->input);
	}
	(void)env;
	return (0);
}
