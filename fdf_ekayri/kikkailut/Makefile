NAME = tutorial

SOURCES = hearts_und_turd.c

OBJECTS = $(subst .c,.o,$(SOURCES))

#FLAGS = -Wall -Wextra #-Werror
#LINKS = -I libft -L libft \
 #   -I /usr/local/include -L /usr/local/lib \
  #  -l mlx -l ft -framework OpenGL -framework Appkit

LINKS = -I /usr/X11/include -g -L /usr/X11/lib -lX11 -lmlx -lXext

# Remember to implement your rules...

#$(NAME): $(OBJECTS)
 #   gcc $(SOURCES) -o $(NAME) $(FLAGS) $(LINKS)

$(NAME):
	gcc $(LINKS) $(SOURCES) libft/libft.a

clean: