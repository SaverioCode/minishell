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

# define T_OPR 1
# define T_CMD
# define T_VAR
# define T_SPR

typedef struct s_expr
{
	
}	t_expr;

# define ROOT 00000001
# define AND  00000011
# define OR   00000111
# define PIPE 00001111

typedef struct s_primary
{
	char		type;
	int			status;
	char		*output;
	t_primary	*next;
	t_expr		*expr;
}	t_primary;

#endif