/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 07:32:30 by sav               #+#    #+#             */
/*   Updated: 2023/07/17 13:44:22 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "./libft/libft.h"

typedef struct s_node	t_node;
typedef struct s_env	t_env;
typedef struct s_info	t_info;

typedef enum e_cmd
{
	BI_NULL,
	BI_CD,
	BI_ECHO,
	BI_ENV,
	BI_EXIT,
	BI_EXPORT,
	BI_PWD,
	BI_UNSET
}	t_bi_cmd;

int			bi_cd(t_info *info, char **args);
__int8_t	bi_echo(char **args);
int			bi_env(t_env *node, char **args);
int			bi_exit(t_info *info, char **args);
__int8_t	bi_export(t_info *info, char **args);
void		bi_add_export_var(t_info *info, char *arg, __int8_t *status);
int			bi_pwd(char **args);
char		*bi_get_cwd(void);
int			bi_unset(t_info *info, char **args);

#endif