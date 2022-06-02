# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/19 15:44:35 by jpuronah          #+#    #+#              #
#    Updated: 2022/06/02 12:46:30 by jpuronah         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
SOURCES = main.c read_and_save_map.c vectors.c graphics.c image.c keyboard.c map_utility.c
INCLUDES = fdf.h
FLAGS = -Wconversion -Wall -Wextra -Werror
LINKS = -I /usr/X11/include -g -L /usr/X11/lib -lX11 -lmlx -lXext
LIBFT = libft/libft.a

all: lib $(NAME)

lib:
	make -C ./libft/

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
