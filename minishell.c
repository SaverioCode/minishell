/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:51:46 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/27 20:55:37 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_node		*root;
	t_info		*info;

	ms_check_input(ac, av);
	info = NULL;
	info = ft_calloc(1, sizeof(t_info));
	ms_init_tinfo(info, env);
	ms_get_prompt_str(info);
	// ms_set_signals();
	ms_init_shell();
	while (1)
	{
		root = NULL;
		root = ft_calloc(1, sizeof(t_node));
		ms_init_tnode(root);
		ms_handle_input(info);
		ps_parser(root, info->input);
		ms_execute_tree(root, info);
		ms_free(root, NULL);
		free(info->input);
		info->input = NULL;
	}
	(void)env;
	return (0);
}
