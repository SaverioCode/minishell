# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/17 15:34:23 by fgarzi-c          #+#    #+#              #
#    Updated: 2023/07/14 20:01:24 by fgarzi-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell.a
SRCS = ms_free.c ms_init_shell.c ms_init_structs.c ms_input.c \
	ms_execution.c ms_execution_utils.c ms_execution_utils_2.c \
	ms_handle_cmd.c ms_cmd_paths.c ms_handle_oprs.c ms_set_termios.c \
	ms_env_utils.c ms_handle_cmd_utils.c ms_free_2.c ms_handle_oprs_utils.c
OBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I ../include

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
