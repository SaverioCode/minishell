# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/01 11:50:39 by fgarzi-c          #+#    #+#              #
#    Updated: 2023/05/09 19:42:59 by fgarzi-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIB_L = ./libft/libft.a
LIB_R = ./readline/libreadline.a
LIB_RH = ./readline/libhistory.a
LIBS = $(LIB_L) $(LIB_R) $(LIB_RH)
SRCS = minishell.c init_shell.c input.c
OBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror

all:
	@make -C ./libft
	@make -C ./src
	@$(CC) $(CFLAGS) -c $(SRCS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -lcurses -o $(NAME)

config:
	@cd readline && sh ./include/configure && cd ..
	@make -C ./include/readline

clean:
	@make clean -C ./libft
	@make clean -C ./src
	@rm -f $(OBJS)
	
fclean: clean
	@make clean -C ./readline
	@make fclean -C ./libft
	@make fclean -C ./src
	@rm -f $(NAME)
	
re: fclean all
	@make re -C ./libft
	@make re -C ./src

.PHONY: all clean fclean re
