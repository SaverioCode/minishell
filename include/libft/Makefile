# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sav <sav@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/01 17:28:53 by fgarzi-c          #+#    #+#              #
#    Updated: 2023/06/24 03:57:40 by sav              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRCS = ft_strlen.c ft_error.c ft_numlen.c ft_calloc.c ft_itoa.c \
	ft_atoi.c ft_strncmp.c ft_isprint.c ft_strchr.c ft_trim.c \
	ft_getstr_from_to.c ft_isdigit.c ft_biarrlen.c ft_strjoin.c \
	ft_strcpy.c ft_push_str.c ft_strictcmp.c ft_isalpha.c ft_find_char.c

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
