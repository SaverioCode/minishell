/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 23:15:57 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/19 05:59:36 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define AND	0b10000010
# define OR  	0b10000011
# define PIPE	'|'
# define CHAR	0b10000100
# define INP	'<'
# define HDOC	0b10000101
# define OUT 	'>'
# define APP	0b10000110

typedef struct s_cmd
{
	char	*cmd;
	char	**args;
}	t_cmd;

typedef struct s_opr
{
	char			token;
	int				fd;
	char			*arg;
	struct s_opr	*next;
}	t_opr;

typedef struct s_node
{
	char			token;
	int				fd_output;
	char			*exp;
	t_opr			*opr;
	t_cmd			*cmd;
	struct s_node	*subshl;
	struct s_node	*next;
	struct s_node	*back;
}	t_node;

void	init_tnode(t_node *node);
void	init_topr(t_opr *node);
void	init_tcmd(t_cmd *node);
char	lx_which_token(char *str);
void	lx_check_quotes(int *flag, char c);
int		lx_token_check(int *token, char new_token, int *brkts);
int		lexical_check(char *input, int flag);
void	ft_parser(t_node *node, char *input);
void	organize_exp(t_node *node);
void	ps_expander(t_node *node, t_env *env);
char	*ps_quotes_cleaner(char *str);

#endif
