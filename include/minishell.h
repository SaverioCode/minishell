/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:51:09 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/08 13:05:00 by fgarzi-c         ###   ########.fr       */
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
	char	*starting_input;
	char	*current_input;
}	t_info;

void	set_tenv(t_env *node);
void	set_tinfo(t_info *info);
void	ft_free(t_node *node, t_info *info);
void	ft_check_input(int ac, char **av);
void	ft_init_shell(void);
char	*ft_print_prompt(void);

#endif
