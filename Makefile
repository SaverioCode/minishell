# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/01 11:50:39 by fgarzi-c          #+#    #+#              #
#    Updated: 2023/05/03 22:20:25 by fgarzi-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIB_L = ./libft/libft.a
LIB_R = ./readline/libreadline.a
LIB_RH = ./readline/libhistory.a
SRCS = minishell.c init_shell.c
OBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(%.c)
	@sh ./readline/configure
	@make -C ./readline
	@make -C ./libft
	@$(CC) $(CFLAGS) -c $(SRCS)
	@$(CC) $(CFLAGS) $(LIB_L) $(OBJS) $(LIB_R) $(LIB_RH) -lcurses -o $(NAME)

%.c: %.o
	@$(CC) $(CFLAGS) -o $<

clean:
	@make clean -C ./readline
	@make clean -C ./libft
	@rm -f $(OBJS)
	
fclean: clean
	@make fclean -C ./libft
	@rm -f $(NAME)
	
re: fclean all
	@make re -C ./libft

.PHONY: all clean fclean re