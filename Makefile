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

NAME = nm

NAME2 = otool

SRC_FOLDER = srcs

SRCS = $(addprefix $(SRC_FOLDER)/, $(NAME) $(NAME2))

all : $(NAME) $(NAME2)

$(NAME):
	make -C $(SRC_FOLDER)/$@
	mv ft_$@ .

$(NAME2):
	make -C $(SRC_FOLDER)/$@
	mv ft_$@ .

clean :
	make clean -C $(SRCS)

fclean :
	make fclean -C $(SRCS)

re : fclean all

.PHONY: $(NAME) $(NAME2)