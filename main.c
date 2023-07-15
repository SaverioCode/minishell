/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:51:46 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/07/15 23:36:54 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_node		*root;
	t_info		*info;

	ms_check_input(ac, av);
	ms_set_termios();
	info = ft_calloc(1, sizeof(t_info));
	ms_init_tinfo(info, env);
	ms_get_prompt_str(info);
	ms_print_header();
	while (1)
	{
		root = ft_calloc(1, sizeof(t_node));
		ms_init_tnode(root);
		info->root = root;
		ms_handle_input(info);
		ps_parser(root, info->input);
		free(info->input);
		info->input = NULL;
		ms_execute_tree(root, info);
		info->status = 0;
		ms_free(root, NULL);
	}
	return (0);
}
