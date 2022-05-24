///* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:43:12 by jpuronah          #+#    #+#             */
/*   Updated: 2022/05/23 16:26:16 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define WIN_WIDTH 720
# define WIN_HEIGHT 360
# define WHITE 0xFFFFFF

# include <mlx.h>
# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <X11/keysym.h>

typedef struct s_vector
{
	int			x;
	int			y;
	int			z;
}				t_vector;

typedef struct s_map
{
	int			width;
	int			height;
	t_vector	**vectors;
}				t_map;

typedef struct s_mlx
{
	void		*mlxptr;
	void		*winptr;
	t_map		*map;
}				t_mlx;

void		printf_error(char *reason);

t_map		*init_map(void);
t_map		*malloc_map(t_map *tmp);
void		read_and_save_map(int fd);
void		get_map_parameters(char *line, t_map *map);

t_vector	**get_vectors(char *save, t_map *map);
t_map		*vectors_for_map(char *save, t_map *map);

void		graphics(t_map *map, char *window_title);

#endif
