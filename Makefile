# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/01 11:50:39 by fgarzi-c          #+#    #+#              #
#    Updated: 2023/05/19 19:39:54 by fgarzi-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIB_L = ./libft/libft.a
LIB_R = ./include/readline/libreadline.a
LIB_RH = ./include/readline/libhistory.a
LIB_M = ./src/minishell.a
LIB_P = ./src/parser/parser.a
LIBS = $(LIB_L) $(LIB_R) $(LIB_RH) $(LIB_P) $(LIB_M)
SRCS = minishell.c
OBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror

all:
	@make -C ./libft
	@make -C ./src
	@$(CC) $(CFLAGS) -c $(SRCS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -lcurses -o $(NAME)

config:
	@cd include/readline && sh configure && cd ../../
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
