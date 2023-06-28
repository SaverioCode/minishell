# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sav <sav@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/17 15:34:10 by fgarzi-c          #+#    #+#              #
#    Updated: 2023/06/27 23:34:28 by sav              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = parser.a
SRCS = lexical.c lexical_utils.c ps_organize_exp.c ps_organize_exp_utils.c \
	parser.c ps_quotes_cleaner.c ps_expander.c ps_wildcard.c
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
