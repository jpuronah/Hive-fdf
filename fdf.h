/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:18:34 by jpuronah          #+#    #+#             */
/*   Updated: 2022/06/12 20:05:51 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define WIN_WIDTH 500
# define WIN_HEIGHT 500
# define WHITE 0xFFFFFF

# include <mlx.h>
# include "libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <limits.h>
# include <stdio.h>
//printf poiess!

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

typedef struct s_angle
{
	double		offsetx;
	double		offsety;
	double		x;
	double		y;
	double		scale;
}				t_angle;

typedef struct s_mlx
{
	void		*mlxptr;
	void		*winptr;
	int			projection;
	int			end;
	t_map		*map;
	t_angle		*angle;
	t_image		*image;
}				t_mlx;

typedef struct s_line_clip
{
	int			region1;
	int			region2;
	int			drawroutine;
	t_vector	tmp_vec;
}				t_line_clip;

void		print_error(char *reason);
void		read_and_save_map(int fd, t_mlx *mlx);

t_map		*init_map(void);
void		check_line(char *line, t_mlx *mlx);
void		map_depth(t_map *map);
char		*save_save(char *save, char *line);
t_map		*vectors_for_map(char *save, t_map *map);

void		graphics(t_map *map, char *window_title);
void		render(t_mlx *mlx);
int			cohen_sutherland_lineclip(t_vector *vector1, t_vector *vector2);

t_vector	vector_list(t_mlx *mlx, int x, int y);
t_vector	set_projection_1(t_vector two_d, t_mlx *mlx);
t_vector	set_projection_2_and_0(t_vector two_d, t_mlx *mlx);

t_image		*new_image(t_mlx *mlx);
t_image		*delete_image(t_mlx *mlx, t_image *img);
void		clear_image(t_image *image);
void		put_pixel_in_image(t_image *image, int x, int y, int color);

int			key_event(int key, t_mlx *mlx);
void		menu(t_mlx *mlx);

double		ft_abs_db(double i);
double		ft_max_double(double a, double b);
double		calculate_delta(t_vector vec1, t_vector vec2, int letter);
void		finish_line_and_one_point(t_vector vec1, t_vector end, t_mlx *mlx);
int			delete_save_and_map(char *save, t_map **map);

#endif
