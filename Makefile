# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/01 11:50:39 by fgarzi-c          #+#    #+#              #
#    Updated: 2023/05/28 18:35:50 by fgarzi-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT = ./include/libft
READLINE = ./include/readline
LIB_L = $(LIBFT)/libft.a
LIB_R = $(READLINE)/libreadline.a
LIB_RH = $(READLINE)/libhistory.a
LIB_M = ./src/minishell.a
LIB_P = ./src/parser/parser.a
LIBS = $(LIB_L) $(LIB_R) $(LIB_RH) $(LIB_P) $(LIB_M)
SRCS = minishell.c
OBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror 

all:
	@make -C $(LIBFT)
	@make -C ./src/parser
	@make -C ./src
	@$(CC) -I include $(CFLAGS) -c $(SRCS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -lcurses -o $(NAME)

config:
	@cd $(READLINE) && sh configure && cd ../../
	@make -C $(READLINE)

clean:
	@make clean -C $(LIBFT)
	@make clean -C ./src/parser
	@make clean -C ./src
	@rm -f $(OBJS)
	
fclean: clean
	# @make clean -C $(READLINE)
	@make fclean -C $(LIBFT)
	@make fclean -C ./src/parser
	@make fclean -C ./src
	@rm -f $(NAME)
	
re: fclean all
	@make re -C $(LIBFT)
	@make re -C ./src/parser
	@make re -C ./src

.PHONY: all clean fclean re
