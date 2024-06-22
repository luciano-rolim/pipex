# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/23 12:57:38 by lmeneghe          #+#    #+#              #
#    Updated: 2024/06/21 09:56:30 by lmeneghe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libprintf.a

CFLAGS = -Wall -Wextra -Werror -fPIC

CFILES = ft_printf.c num_functions.c

OFILES = $(CFILES:%.c=%.o)

%.o: %.c
	@cc $(CFLAGS) -c $< -o $@

$(NAME): $(OFILES)
	@ar rc $(NAME) $(OFILES)
	@ranlib $(NAME)

all: $(NAME)

clean:
	@rm -f $(OFILES)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.DEFAULT_GOAL := all

.PHONY: all clean fclean re
