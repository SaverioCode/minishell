/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 23:15:57 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/05 00:14:38 by fgarzi-c         ###   ########.fr       */
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
	char		type;
	short int	status;
	int			fd_output;
	char		*exp;
	t_cmd		*right;
	t_opr		*left;
}	t_node;

void	ft_parser(t_node *exp, char *input);
void	ft_separete_exps(t_node *exp, char *input);

#endif
