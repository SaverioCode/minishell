/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:51:09 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/07/13 22:39:51 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include "./parser.h"
# include "./built_in.h"
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
	char			*path;
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

typedef struct s_env
{
	int				env;
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_info
{
	t_node	*root;
	t_child	*child;
	t_fd	*fd_lis;
	t_env	*env;
	char	token;
	char	*input;
	int		stdin_clone;
	int		stdout_clone; // i think I never use it //
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
void	ms_free_info(t_info *info);
void	ms_check_input(int ac, char **av);
void	ms_init_shell(void);
void	ms_set_termios(void);
void	ms_handle_input(t_info *info);
void	ms_set_env(t_info *info, char **env);
char	*ms_get_env_value(t_info *info, char *name);
void	ms_execute_tree(t_node *node, t_info *info);
void	ms_waitpid(pid_t pid, t_info *info);
int		ms_handle_oprs(t_info *info, t_opr *opr, t_fd *fd_node);
void	ms_handle_cmd(t_node *node, t_info *info);
void	ms_format_cmd(t_cmd *cmd, t_info *info);
int		ms_cmd_built_in(t_info *info, t_node *node);
void	ms_init_pipe(char token, t_info *info);
void	ms_init_pipe_child(t_node *node, t_info *info);
void	ms_end_execution(char token, t_info *info, pid_t pid);
void	ms_end_execution_child(t_info *info);
int		ms_check_fd_lis(t_fd *fd_lis, int fd);
void	ms_store_pid(t_info *info, pid_t pid);
void	ms_waitchild(t_info *info);
void	ms_restore_fd(t_info *info);

#endif
