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
# include <math.h>

int	scale;

typedef struct		s_cam
{
	double		offsetx;
	double		offsety;
	double		x;
	double		y;
	int			scale;
	double		**matrix;
}					t_cam;

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
	int			param;
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

void		printf_error(char *reason);

t_map		*init_map(void);
t_map		*malloc_map(t_map *tmp);
void		read_and_save_map(int fd, int scale, char *title);
void		get_map_parameters(char *line, t_map *map);

t_vector	**get_vectors(char *save, t_map *map);
t_map		*vectors_for_map(char *save, t_map *map);

void		graphics(t_map *map, char *window_title);
t_mlx		*malloc_mlx(void);
t_image		*new_image(t_mlx *mlx);

t_image		*new_image(t_mlx *mlx);
t_image		*delete_image(t_mlx *mlx, t_image *img);
void		reset_image(t_image *image);
void		put_pixel_in_image(t_image *image, int x, int y, int color);

#endif
