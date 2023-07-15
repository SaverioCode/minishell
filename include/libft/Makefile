# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/13 18:36:56 by fgarzi-c          #+#    #+#              #
#    Updated: 2023/07/15 23:50:48 by fgarzi-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRCS = ft_strlen.c ft_error.c ft_numlen.c ft_calloc.c ft_itoa.c \
	ft_atoi.c ft_strcmp.c ft_strncmp.c ft_isprint.c ft_strchr.c ft_trim.c \
	ft_getstr_from_to.c ft_isdigit.c ft_biarrlen.c ft_strjoin.c \
	ft_strcpy.c ft_push_str.c ft_strictcmp.c ft_isalpha.c ft_find_char.c \
	ft_append_arr.c ft_free.c ft_append_str.c ft_lexical_sort_arr.c \

OBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(%.c)
	@$(CC) $(CFLAGS) -c $(SRCS)
	@ar rcs $(NAME) $(OBJS)

%.c: %.o
	@$(CC) $(CFLAGS) -o $<

clean:
	@rm -f $(OBJS)
	
fclean: clean
	@rm -f $(NAME)
	
re: fclean all

.PHONY: all clean fclean re
