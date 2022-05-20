# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/19 15:44:35 by jpuronah          #+#    #+#              #
#    Updated: 2022/05/20 17:16:03 by jpuronah         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
SOURCES = main.c map.c vectors.c graphics.c
INCLUDES = fdf.h
FLAGS = -Wall -Wextra -Werror 
LINKS = -I /usr/X11/include -g -L /usr/X11/lib -lX11 -lmlx -lXext
LIBFT = libft/libft.a

all: lib $(NAME)

lib:
	make -C ./libft/

#make libft:lle oma homma

$(NAME):
	gcc $(FLAGS) -o $(NAME) $(LINKS) $(SOURCES) $(LIBFT)

nf:
	gcc -o $(NAME) $(LINKS) $(SOURCES) $(LIBFT)

leaks:
	gcc $(FLAGS) -o $(NAME) $(LINKS) $(SOURCES) $(LIBFT) -fsanitize=address

clean:
	rm -f *.o
	rm -f ./libft/*.o

fclean: clean
	rm -f fdf
	rm -f ./libft/libft.a

re: fclean all
