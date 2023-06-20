# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/01 11:50:39 by fgarzi-c          #+#    #+#              #
#    Updated: 2023/06/20 22:51:19 by fgarzi-c         ###   ########.fr        #
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
LIB_BI = ./src/built_in/built_in.a
LIBS = $(LIB_R) $(LIB_RH) $(LIB_P) $(LIB_M) $(LIB_L) $(LIB_BI)
SRCS = minishell.c
OBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude

#-lreadline -lhistory 

all: $(NAME)

$(NAME): $(OBJS)
	@make -s -C $(LIBFT)
	@make -s -C ./src/parser
	@make -s -C ./src/built_in
	@make -s -C ./src
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS) -lncurses -lreadline

config:
	@cd $(READLINE) && sh configure && cd ../../
	@make -C $(READLINE)

clean:
	@make clean -s -C $(LIBFT)
	@make clean -s -C ./src/parser
	@make clean -s -C ./src/built_in
	@make clean -s -C ./src
	@rm -f $(OBJS)
	
fclean: clean
	# @make clean -C $(READLINE)
	@make fclean -s -C $(LIBFT)
	@make fclean -s -C ./src/parser
	@make fclean -s -C ./src/built_in
	@make fclean -s -C ./src
	@rm -f $(NAME)
	
re: fclean all
	@make re -s -C $(LIBFT)
	@make re -s -C ./src/parser
	@make re -s -C ./src

.PHONY: all clean fclean re