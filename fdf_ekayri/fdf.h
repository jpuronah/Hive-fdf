/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 09:57:56 by jpuronah          #+#    #+#             */
/*   Updated: 2022/04/26 14:35:58 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define WIN_WIDTH 720
# define WIN_HEIGHT 360

# include "mlx.h"
# include "libft/libft.h"
# include <X11/keysym.h>

# include <fcntl.h>
# include <stdio.h>
# include <limits.h>

typedef struct		s_cam
{
	double		offsetx;
	double		offsety;
	double		x;
	double		y;
	int			scale;
	double		**matrix;
}					t_cam;

typedef struct		s_vector
{
	double		x;
	double		y;
	double		z;
	int			color;
}					t_vector;

typedef struct		s_map
{
	int			width;
	int			height;
	int			depth_min;
	int			depth_max;
	t_vector	**vectors;
}					t_map;

typedef struct		s_image
{
	void		*image;
	char		*ptr;
	int			bpp;
	int			line_bytes;
	int			endian;
}					t_image;

typedef struct		s_mouse
{
	char		isdown;
	int			x;
	int			y;
	int			lastx;
	int			lasty;
}					t_mouse;

typedef struct		s_mlx
{
	void		*mlxptr;
	void		*window;
	t_image		*image;
	t_map		*map;
	t_cam		*cam;
	t_mouse		*mouse;
	double		**zbuf;
}					t_mlx;

/*
typedef struct		s_line
{
	t_vector	start;
	t_vector	stop;
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			err;
	int			err2;
}					t_line;
*/

int		exit_with_esc(int key, t_mlx *mlx);
int		hook_mousemove(int x, int y, t_mlx *mlx);
int		hook_mouseup(int button, int x, int y, t_mlx *mlx);
int		hook_mousedown(int button, int x, int y, t_mlx *mlx);

int		lineclip(t_vector *p1, t_vector *p2);
int		read_file_and_make_map(int fd, t_map **map);

void		render(t_mlx *mlx);

t_map	*malloc_map(int width, int height);

void	fill_colors(t_map *m);
void	image_set_pixel(t_image *image, int x, int y, int color);
void	map_depth(t_map *m);
void	print_error(char *reason);

t_mlx	*initialize_mlx(char *name);

t_image	*del_image(t_mlx *mlx, t_image *img);

t_vector	*get_vector_for_map(int x, int y, char *str);

int		clerp(int c1, int c2, double p);
double	ft_lerp(double first, double second, double p);
int		ft_lerpi(int first, int second, double p);
double	ft_ilerp(double val, double first, double second);

#endif
