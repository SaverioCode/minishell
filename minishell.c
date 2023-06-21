/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:51:46 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/06/21 15:54:01 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_node		*root;
	t_info		*info;

	ms_check_input(ac, av);
	ms_set_termios();
	info = NULL;
	info = ft_calloc(1, sizeof(t_info));
	ms_init_tinfo(info, env);
	ms_get_prompt_str(info);
	ms_init_shell();
	while (1)
	{ 
		root = NULL;
		root = ft_calloc(1, sizeof(t_node));
		ms_init_tnode(root);
		info->root = root;
		ms_handle_input(info);
		ps_parser(root, info->input);
		free(info->input);
		info->input = NULL;
		ms_execute_tree(root, info);
		info->status = 0; /// to modify in order to have access to variable $? with last exit status /// 
		ms_free(root, NULL);
	}
	return (0);
}
