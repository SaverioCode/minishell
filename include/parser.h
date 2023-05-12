/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 23:15:57 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/12 06:49:52 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define AND	0b10000010
# define OR  	0b10000011
# define PIPE	'|'
# define CHAR	0b10000100
# define INP	'<'
# define INP2	0b10000101
# define OUT 	'>'
# define OUT2	0b10000110

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
	struct s_node	*back;
}	t_node;

void	set_tnode(t_node *node);
void	set_topr(t_opr *node);
void	set_tcmd(t_cmd *node);
void	lx_check_quotes(int *flag, char c);
int		lx_token_check(char token, char new_token, int *brkts);
int		lexical_check(char *input);
void	ft_parser(t_node *node, char *input);
int		get_token(t_node *node, t_info *info, int i);
int		ft_create_exps_tree(t_node *node);

#endif
