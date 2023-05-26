/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:51:46 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/26 09:09:37 by fgarzi-c         ###   ########.fr       */
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
	init_tinfo(info, env);
	ft_get_prompt_str(info);
	// set_signals();
	ft_init_shell();
	while (1)
	{
		root = NULL;
		root = ft_calloc(1, sizeof(t_node));
		init_tnode(root);
		ft_handle_input(info);
		ps_parser(root, info->input);
		ft_execute_tree(root, info);
		ft_free(root, NULL);
		free(info->input);
		info->input = NULL;
	}
	(void)env;
	return (0);
}
