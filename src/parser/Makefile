# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgarzi-c <fgarzi-c@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/17 15:34:10 by fgarzi-c          #+#    #+#              #
#    Updated: 2023/07/13 17:47:42 by fgarzi-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = parser.a
SRCS = ps_lexical.c ps_lexical_utils.c ps_organize_exp.c ps_organize_exp_utils.c \
	ps_parser.c ps_quotes_cleaner.c ps_expander.c ps_wildcard.c ps_wildcard_utils.c \
	ps_wildcard_utils_2.c
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
