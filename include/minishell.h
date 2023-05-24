/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:51:09 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/24 06:24:07 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../src/libft/libft.h"
# include "./readline/readline.h"

# define AND	0b01000001
# define OR  	0b01000011
# define PIPE	'|'
# define CHAR	0b01000100
# define INP	'<'
# define HDOC	0b01000101
# define OUT 	'>'
# define APP	0b01000110

typedef struct s_cmd_path
{
	char				*str;
	struct s_cmd_path	*next;
}	t_path;

typedef struct s_fd
{
	int			std_fd;
	int			file_fd;
	struct s_fd	*next;
}	t_fd;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_info
{
	char	**env;
	char	*input;
	int		stdin_clone;
	int		stdout_clone;
	int		status;
	char	*prompt;
}	t_info;

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
	t_opr			*opr;
	t_cmd			*cmd;
	struct s_node	*subshl;
	struct s_node	*next;
	struct s_node	*back;
}	t_node;


void	ft_set_starting_env(char **env, t_info *info);
void	ft_get_prompt_str(t_info *info);
void	init_tenv(t_env *node);
void	init_tinfo(t_info *info, char **env);
void	ft_free(t_node *node, t_info *info);
void	ft_check_input(int ac, char **av);
void	ft_init_shell(void);
void	ft_handle_input(t_info *info);
void    ft_execute_tree(t_node *node, t_info *info);
t_node	*ls_get_last_tnode(t_node *node, char c);
t_opr	*ls_get_last_topr(t_opr *opr);


///	Parser ///

void	init_tnode(t_node *node);
void	init_topr(t_opr *node);
void	init_tcmd(t_cmd *node);
char	lx_which_token(char *str);
void	lx_check_quotes(int *flag, char c);
int		lx_token_check(int *token, char new_token, int *brkts);
int		lexical_check(char *input, int flag);
void	ft_parser(t_node *node, char *input);
void	organize_exp(t_node *node, char *exp);
void	ps_expander(t_node *node, t_env *env);
char	*ps_quotes_cleaner(char *str);

#endif
