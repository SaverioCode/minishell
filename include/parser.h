/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 23:15:57 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/12 05:00:43 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define END 	0b10000001
// # define AND1	'&'
# define AND	0b10000010
# define OR  	0b10000011
# define PIPE	'|'
# define CHAR	0b10000100
# define INP	'<'
# define INP2	0b10000101
# define OUT 	'>'
# define OUT2	0b10000110
// # define OBRK	'('
// # define CBRK	')'

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

typedef struct s_node
{
	short int		shlvl;
	char			token;
	short int		status;
	int				fd_output;
	char			*exp;
	t_opr			*opr;
	t_cmd			*cmd;
	struct s_node	*subshl;
	struct s_node	*next;
}	t_node;

/////// CHECK IF DO THE THING WRITTEN BELOW //////////
// in order to keep the work ordered and not having //
// <untype> arguments all functions declarations are //
// in minishell.h //

void	set_tnode(t_node *node);
void	set_topr(t_opr *node);
void	set_tcmd(t_cmd *node);
int		lx_token_check(char token, char new_token, int *brkts);
int		ft_parser(t_node *exp, t_info *input);
int		ft_create_nodes(t_node *exp, t_info *info, int *flag, int *brackets);
int		ft_check_flag(int *flag, char c, int *brackets);
int		get_token(t_node *node, t_info *info, int i);
int		ft_create_exps_tree(t_node *node);

#endif
