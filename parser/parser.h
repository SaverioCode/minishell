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

typedef struct s_cmd
{
	char	*cmd;
	char	**args;
}	t_cmd;

typedef struct s_opr
{
	char	*fd;
	char	*arg;
	t_opr	*next;
}	t_opr;

typedef struct s_exp
{
	char	*exp;
	t_cmd	*right;
	t_opr	*left;
}	t_exp;

# define ROOT 0b10000001
# define AND  0b10000010
# define OR   0b10000011
# define PIPE 0b10000100

typedef struct s_primary
{
	char		type;
	short int	status;
	int			fd;
	t_primary	*right;
	t_expr		*left;
}	t_primary;

#endif