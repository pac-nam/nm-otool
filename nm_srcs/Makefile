# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbleuse <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/08 10:34:52 by tbleuse           #+#    #+#              #
#    Updated: 2018/10/23 13:48:46 by tbleuse          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_nm

CC = gcc

FLAGS = -Wall -Wextra -Werror

LIBDIR		=	../libft
LIB			=	libft.a

SRC_FOLDER = srcs

INCLUDE_FOLDER = includes

OBJ_FOLDER = objs

SRC_NAME	=	main.c						\
				ft_buff.c					\
				ft_nm_parse.c				\
				ft_nm_this_file.c			\
				ft_nm_64.c					\
				ft_hexdump.c				\
				ft_check.c					\
				ft_print_result.c			\
				ft_symbol.c					\
				ft_nm_32.c					\
				multi_architectural.c		\
				ft_rev.c					\
				ft_nm_fat_reverse.c			\
				ft_options.c				\
				ft_end_options.c			\
				ft_insert_sort_functions.c	\

SRC = $(addprefix $(SRC_FOLDER)/, $(SRC_NAME))

OBJ = $(addprefix $(OBJ_FOLDER)/, $(SRC_NAME:.c=.o))

all : $(LIBDIR)/$(LIB) $(NAME)

$(NAME): $(OBJ_FOLDER) $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) $(LIBDIR)/$(LIB) -I$(INCLUDE_FOLDER) -o $(NAME)
	@echo "\033[32m[ ✔ ] $@ compiled\033[0m"

$(OBJ_FOLDER):
	@mkdir -p $@
	@mkdir -p $(OBJ_FOLDER)
	@echo "creating $(NAME) object..."

$(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.c
	@$(CC) -I$(INCLUDE_FOLDER) -c $(FLAGS) $< -o $@

$(LIBDIR)/$(LIB):
	@make -C $(LIBDIR)

clean :
	@make clean -C $(LIBDIR)
	@/bin/rm -rf $(OBJ_FOLDER)
	@echo "\033[33m[ ✔ ] $(NAME) objects deleted\033[0m"

fclean : clean
	@make fclean -C $(LIBDIR)
	@/bin/rm -f $(NAME)
	@echo "\033[33m[ ✔ ] $(NAME) deleted\033[0m"

lib : all clean

re : fclean all

.PHONY: