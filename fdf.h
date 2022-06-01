/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:18:34 by jpuronah          #+#    #+#             */
/*   Updated: 2022/06/01 18:44:47 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define WHITE 0xFFFFFF

# include <mlx.h>
# include "libft/libft.h"
# include <fcntl.h>
# include <math.h>
//# include <stdio.h>
//# include <X11/keysym.h>

typedef struct s_cam
{
	double		offsetx;
	double		offsety;
	double		x;
	double		y;
	int			scale;
	double		**matrix;
}				t_cam;

typedef struct s_vector
{
	double		x;
	double		y;
	double		z;
	int			color;
}				t_vector;

typedef struct s_map
{
	int			width;
	int			height;
	int			depth_min;
	int			depth_max;
	t_vector	**vectors;
}				t_map;

typedef struct s_image
{
	void		*image;
	char		*ptr;
	int			bpp;
	int			line_bytes;
	int			endian;
}				t_image;

typedef struct s_mlx
{
	void		*mlxptr;
	void		*winptr;
	t_map		*map;
	t_cam		*cam;
	t_image		*image;
	int			frame;
}				t_mlx;

typedef struct s_line
{
	t_vector	start;
	t_vector	stop;
	int			delta_x;
	int			delta_y;
	int			sx;
	int			sy;
	int			err;
	int			err2;
}				t_line;

void		print_error(char *reason);
//void		free_and_exit(int key, t_mlx *mlx);

void		read_and_save_map(int fd, t_mlx *mlx);
char		*save_save(char *save, char *line);
void		map_depth(t_map *map);
int			delete_save_and_map(char *save, t_map **map);

t_vector	**get_vectors(char *save, t_map *map);
t_map		*vectors_for_map(char *save, t_map *map);
t_vector	get_vector_for_render(t_map *map, int x, int y);
t_vector	project_vector(t_vector v, t_mlx *mlx);

void		graphics(t_map *map, char *window_title);
void		render(t_mlx *mlx);
t_mlx		*malloc_mlx(void);

t_image		*new_image(t_mlx *mlx);
t_image		*delete_image(t_mlx *mlx, t_image *img);
void		reset_image(t_image *image);
void		put_pixel_in_image(t_image *image, int x, int y, int color);

int			key_event(int key, t_mlx *mlx);
void		menu(t_mlx *mlx);

#endif
