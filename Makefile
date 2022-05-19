# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/19 15:44:35 by jpuronah          #+#    #+#              #
#    Updated: 2022/05/19 15:51:06 by jpuronah         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
SOURCES = main.c
INCLUDES = fdf.h

all: $(NAME)

#make libft:lle oma homma

$(NAME):
	gcc -o $(NAME) $(SOURCES) $(INCLUDES)

clean:
	rm -f fdf

fclean: clean
	rm -f 

re:
