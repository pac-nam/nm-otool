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

NAME2 = ft_otool

SRC1 = nm_srcs

SRC2 = otool_srcs

SRCS = $(SRC1) $(SRC2)

all : $(NAME) $(NAME2)

$(NAME):
	make -C $(SRC1)
	mv $@ .

$(NAME2):
	make -C $(SRC2)
	mv $@ .

clean :
	make clean -C $(SRCS)

fclean :
	make fclean -C $(SRCS)

re : fclean all

.PHONY: $(NAME) $(NAME2)