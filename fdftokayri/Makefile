# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/28 14:01:31 by jpuronah          #+#    #+#              #
#    Updated: 2022/04/28 14:05:06 by jpuronah         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
SOURCES = *.c #tänne lista paskaa
FLAGS = -Wall -Wextra -Werror -Wconversion
LINKS = -I /usr/X11/include -g -L /usr/X11/lib -lX11 -lmlx -lXext
LIBFT = libft/libft.a

all: lib $(NAME)

lib:
	make -C ./libft/

$(NAME):
	gcc $(FLAGS) -o $(NAME) $(LINKS) $(SOURCES) $(LIBFT)

noflags:
	gcc -o $(NAME) $(LINKS) $(SOURCES) $(LIBFT)

clean:
	rm -f *.o
	rm -f ./libft/*.o

fclean: clean
	rm -f fdf
	rm -f ./libft/libft.a

re: fclean all