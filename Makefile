# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/19 15:44:35 by jpuronah          #+#    #+#              #
#    Updated: 2022/06/12 17:36:23 by jpuronah         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Tämä jiiriin vielä
NAME = fdf
SOURCES = main.c read_and_save_map.c vectors.c graphics.c graphics_utility.c image.c keyboard.c map_utility.c lineclipper.c
INCLUDES = fdf.h
FLAGS = -Wconversion -Wall -Wextra -Werror
LINKS = -L /usr/local/lib -lmlx -I /usr/local/include -framework OpenGL -framework AppKit
LINKSA = /usr/local/lib/libmlx.a
LINKSHOME = -I /usr/X11/include -g -L /usr/X11/lib -lX11 -lmlx -lXext
LIBFT = libft/libft.a

all: lib $(NAME)

lib:
	make -C ./libft/

$(NAME):
	gcc -g $(FLAGS) -o $(NAME) $(LINKS) $(SOURCES) $(LIBFT)

nf:
	gcc -o $(NAME) $(LINKS) $(SOURCES) $(LIBFT)

leaks:
	make leaks -C ./libft/
	gcc -fsanitize=address -g $(FLAGS) -o $(NAME) $(LINKS) $(SOURCES) $(LIBFT)

clean:
	rm -f *.o
	rm -f ./libft/*.o

fclean: clean
	rm -f fdf
	rm -f ./libft/libft.a

re: fclean all
