# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/19 15:44:35 by jpuronah          #+#    #+#              #
#    Updated: 2022/06/13 13:09:25 by jpuronah         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
SOURCES = main.c read_and_save_map.c vectors.c graphics.c graphics_utility.c \
image.c keyboard.c map_utility.c line_clipper.c
OBJECTIVES = $(SOURCES:.c=.o)
LIBFT = ./libft/
CFLAGS = -Wall -Wextra -Werror 
MLX = -L /usr/local/lib -lmlx -I /usr/local/include
FRAMEWORK = -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME):
	make -C $(LIBFT)
	gcc -c $(CFLAGS) $(SOURCES)
	gcc $(OBJECTIVES) $(CFLAGS) -o $(NAME) $(MLX) -Llibft -lft $(FRAMEWORK)

clean:
	/bin/rm -f $(OBJECTIVES)
	make -C $(LIBFT) clean

fclean: clean
	/bin/rm -f $(NAME)
	make -C $(LIBFT) fclean

re: fclean all
