/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sav <sav@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 07:28:05 by sav               #+#    #+#             */
/*   Updated: 2023/07/13 02:13:14 by sav              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "./libft/libft.h"

typedef struct s_node t_node;
typedef struct s_info t_info;

typedef struct s_wildcard {
	char	*prev;
	char	*after;
	char	*dir;
	char	*prefix;
	char	*suffix;
}	t_wildcard;

char	lx_which_token(char *str);
void	lx_check_quotes(int *flag, char c);
int		lx_token_check(int *token, char new_token, int *brkts);
int		lexical_check(char *input, int flag);
void	ps_parser(t_node *node, char *input);
void	ps_organize_exp(t_node *node, char *exp);
void	ps_add_instruction(t_node *node, char *exp, int from, int *i);
void	ps_expander(t_node *node, t_info *info);
char	**ps_wildcard(char *str);
char	**ps_analyze_string(char *str);//, __uint32_t i);
char	**ps_quotes_cleaner(char **arr);
char	*ps_clean_quotes(char *str);
char	**ps_get_matrix(t_wildcard *info, char *str);

#endif