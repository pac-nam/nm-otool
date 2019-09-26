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

$(NAME): $(SRC1)
	@make -C $(SRC1)
	@mv $(SRC1)/$@ .

$(NAME2): 
	@make -C $(SRC2)
	@mv $(SRC2)/$@ .

clean :
	@make clean -C $(SRC1)
	@make clean -C $(SRC2)

fclean :
	@make fclean -C $(SRC1)
	@make fclean -C $(SRC2)
	@rm -f $(NAME) $(NAME2)

re : fclean all

.PHONY: $(NAME) $(NAME2)