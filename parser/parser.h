/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sav <sav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 23:15:57 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/06 18:33:07 by sav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../libft/libft.h"

# define ROOT 0b10000001
# define AND  0b10000010
# define OR   0b10000011
# define PIPE 0b10000100

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
	char			token;
	short int		status;
	int				fd_output;
	char			*exp;
	t_cmd			*cmd;
	t_opr			*opr;
	struct s_node	*next;
}	t_node;

typedef struct s_input
{
	char	*starting;
	char	*current;
}	t_input;

void	ft_free(t_node *node, t_input *input);
void	ft_parser(t_node *exp, t_input *input);
void	ft_separete_exps(t_node *exp, t_input *inpt);
char	get_token(t_node *node, t_input *input);
t_node	*ls_get_last_node(t_node *node);

#endif
