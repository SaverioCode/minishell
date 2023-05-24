# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/01 11:50:39 by fgarzi-c          #+#    #+#              #
#    Updated: 2023/05/25 00:26:35 by fgarzi-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIB_L = ./src/libft/libft.a
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
	@make -C ./src/libft
	@make -C ./src/parser
	@make -C ./src
	@$(CC) -I include $(CFLAGS) -c $(SRCS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -lcurses -o $(NAME)

config:
	@cd include/readline && sh configure && cd ../../
	@make -C ./include/readline

clean:
	@make clean -C ./src/libft
	@make clean -C ./src/parser
	@make clean -C ./src
	@rm -f $(OBJS)
	
fclean: clean
	# @make clean -C ./readline
	@make fclean -C ./src/libft
	@make fclean -C ./src/parser
	@make fclean -C ./src
	@rm -f $(NAME)
	
re: fclean all
	@make re -C ./src/libft
	@make re -C ./src/parser
	@make re -C ./src

.PHONY: all clean fclean re
