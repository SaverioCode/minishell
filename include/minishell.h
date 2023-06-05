/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:51:09 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/06/05 19:37:54 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include "./readline/readline.h"

# define AND	0b01000001
# define OR  	0b01000011
# define PIPE	'|'
# define CHAR	0b01000100
# define INP	'<'
# define HDOC	0b01000101
# define OUT 	'>'
# define APP	0b01000110

typedef struct s_child
{
	pid_t			pid;
	struct s_child	*next;
}	t_child;

typedef struct s_fd
{
	int			fd;
	int			fd_clone;
	int			file_fd;
	struct s_fd	*next;
}	t_fd;

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

typedef struct s_info
{
	t_node	*root;
	t_child	*child;
	char	token;
	char	**env;
	char	*input;
	int		stdin_clone;
	int		stdout_clone;
	int		status;
	char	*prompt;
	int		pipe;
	int		subshl;
	int		fd[2];
}	t_info;

void	ms_init_tnode(t_node *node);
void	ms_init_topr(t_opr *node);
void	ms_init_tcmd(t_cmd *node);
void	ms_get_prompt_str(t_info *info);
void	ms_init_tinfo(t_info *info, char **env);
void	ms_free(t_node *node, t_info *info);
void	ms_check_input(int ac, char **av);
void	ms_init_shell(void);
void	ms_handle_input(t_info *info);
void    ms_execute_tree(t_node *node, t_info *info);
void 	ms_waitpid(pid_t pid, t_info *info);
int		ms_handle_oprs(t_info *info, t_opr *opr, t_fd *fd_node);
t_fd	*create_fd_node(t_fd *node);
void	ms_handle_cmd(t_node *node, t_info *info, t_fd *fd_lis);
void	ms_format_cmd(t_cmd *cmd, char **env);
int		ms_execute_cmd(t_node *node, t_cmd *cmd, t_info *info);
void	ms_init_pipe(char token, t_info *info);
void	ms_init_pipe_child(t_node *node, t_info *info);
void	ms_end_execution(char token, t_info *info, pid_t pid);
void	ms_end_execution_child(t_node *node, t_info *info);
void	ms_store_pid(t_info *info, pid_t pid);
void	ms_waitchild(t_info *info);

///	Parser ///

char	lx_which_token(char *str);
void	lx_check_quotes(int *flag, char c);
int		lx_token_check(int *token, char new_token, int *brkts);
int		lexical_check(char *input, int flag);
void	ps_parser(t_node *node, char *input);
void	ps_organize_exp(t_node *node, char *exp);
void	ps_add_instruction(t_node *node, char *exp, int from, int *i);
void	ps_expander(t_node *node, char **env);
char	*ps_quotes_cleaner(char *str);

#endif
