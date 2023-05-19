/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:51:09 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/19 05:33:28 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../src/libft/libft.h"
# include "./readline/readline.h"
# include "parser.h"

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_info
{
	t_env	*env;
	char	*input;
	int		stdin_clone;
	int		stdout_clone;
	int		status;
}	t_info;

void	init_tenv(t_env *node);
void	init_tinfo(t_info *info);
void	ft_free(t_node *node, t_info *info);
void	ft_check_input(int ac, char **av);
void	ft_init_shell(void);
void	ft_handle_input(t_info *info);
t_node	*ls_get_last_tnode(t_node *node, char c);
t_opr	*ls_get_last_topr(t_opr *opr);

///	Parser ///


#endif
