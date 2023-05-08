/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 23:15:57 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/08 11:12:29 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../libft/libft.h"

# define ROOT 0b10000001
# define AND  0b10000010
# define OR   0b10000011
# define PIPE 0b10000100

# define TRUE 1
# define FALSE 0

typedef struct s_cmd
{
	char	*cmd;
	char	**args;
}	t_cmd;

typedef struct s_opr
{
	char			*fd;
	char			*arg;
	struct s_opr	*next;
}	t_opr;

typedef struct	s_exp
{
	char			parentesis;
	char			*exp;
	t_cmd			*cmd;
	t_opr			*opr;
	struct t_exp	*next;
}	t_exp;

typedef struct s_node
{
	char			token;
	short int		status;
	int				fd_output;
	t_exp			*exps;
	struct s_node	*next;
}	t_node;

typedef struct s_input
{
	char	*starting;
	char	*current;
}	t_input;

/// eventualy to put this structure in minishell.h and delete the one above ///
// typedef struct s_info
// {
// 	char	**env;
// 	char	*starting_input;
// 	char	*current_input;
// }	t_info;

void	set_tnode(t_node *node);
void	set_texp(t_exp *node);
void	set_topr(t_opr *node);
void	set_tcmd(t_cmd *node);
void	ft_free(t_node *node, t_input *input);
void	ft_parser(t_node *exp, t_input *input);
void	ft_separete_exps(t_node *exp, t_input *inpt);
char	get_token(t_node *node, t_input *input);
void	ft_create_exps_tree(t_node *node);
t_node	*ls_get_last_node(t_node *node);

#endif
