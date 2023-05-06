/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sav <sav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:51:46 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/06 17:44:45 by sav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_root(t_node *root)
{
	root->token = ROOT;
	root->status = 0;
	root->fd_output = 0;
	root->cmd = NULL;
	root->opr = NULL;
	root->next = NULL;
}

int	main(int ac, char **av, char **env)
{
	t_node	root;
	t_input	input;

	ft_check_input(ac, av);
	ft_init_shell();
	set_root(&root);
	while (1)
	{
		input.starting = ft_print_prompt();
		if (!input.starting)
			continue ;
		// just for testing maintaining a clean exit //
		if (input.starting && input.starting[0] == 'q')
		{	
			free(input.starting);
			return (0);
		}
		input.current = input.starting;
		ft_parser(&root, &input);
	}
	(void)env;
	return (0);
}
