# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/20 22:49:33 by fgarzi-c          #+#    #+#              #
#    Updated: 2023/06/20 23:27:25 by fgarzi-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = built_in.a
SRCS = bi_pwd.c bi_cd.c
OBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I ../../include

all: $(%.c)
	@$(CC)  $(CFLAGS) -c $(SRCS) 
	@ar rcs $(NAME) $(OBJS)

%.c: %.o
	@$(CC) $(CFLAGS) -o $<

clean:
	@rm -f $(OBJS)
	
fclean: clean
	@rm -f $(NAME)
	
re: fclean all

.PHONY: all clean fclean re
