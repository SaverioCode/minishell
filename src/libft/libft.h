/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:29:03 by fgarzi-c          #+#    #+#             */
/*   Updated: 2023/05/19 19:33:23 by fgarzi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>

size_t	ft_strlen(char *str);
int		ft_numlen(long long num, int base);
void	ft_error(char *str);
void	*ft_calloc(size_t bytes, size_t size);
int		ft_atoi(const char *str);
char	*ft_itoa(long num);
int		ft_strncmp(char *a, char *b, size_t bytes);
int		ft_isprint(char c);
int		ft_strchr(char *str, char c);
char	*ft_getstr_from_to(char *str, int from, int to);
int		ft_isdigit(char c);
int		ft_str_isdigit(char *str);
size_t	ft_biarrlen(char **arr);
char    *ft_strjoin_sp(char *str1, char *str2);

#endif
