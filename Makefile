# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmeneghe <lmeneghe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/21 09:37:06 by lmeneghe          #+#    #+#              #
#    Updated: 2024/06/21 09:59:10 by lmeneghe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME			= pipex

# Lib Directories
LIBFT_DIR		= ./libft/
PRINTF_DIR		= ./ft_printf/

# Compiler and Flags
CC				= cc
CFLAGS			= -Wall -Wextra -Werror

# Libraries
LIBFT			= $(LIBFT_DIR)libft.a
PRINTF			= $(PRINTF_DIR)libprintf.a

# Source Files
SRC_FILES		= pipex.c \

# Compiler SRC_FILES into .o files
OBJS	= $(SRC_FILES:%.c=%.o)

#Line 1: ensure all .o files are created + libft + printf
#Line 2: compiles everything to generate push_swap program
$(NAME):		$(OBJS) $(LIBFT) $(PRINTF)
				@$(CC) $(OBJS) -L$(LIBFT_DIR) -lft -L$(PRINTF_DIR) -lprintf -o $(NAME)

#Command to execute make inside libft folder and generate libft.a file
$(LIBFT):
				@make -C $(LIBFT_DIR)

#Command to execute make inside printf folder and generate libprintf.a file
$(PRINTF):
				@make -C $(PRINTF_DIR)

#Make instruction on how to compile .o if is not up to date
%.o: %.c
			@$(CC) $(CFLAGS) -c $< -o $@

#Standard all command
all:			$(NAME)

#clean > removes all .o files on all directories
clean:
				@find . -name "*.o" -delete

#fclean > call clean + remove push_swap file
#extra rule to fclean the libft library
fclean:			clean
				@rm -f $(NAME)
				@make fclean -C $(LIBFT_DIR)
				@make fclean -C $(PRINTF_DIR)

#Standard re command
re:				fclean all

#Standard .PHONY protection
.PHONY:			all clean fclean re
