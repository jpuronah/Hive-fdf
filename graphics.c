/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:27:13 by jpuronah          #+#    #+#             */
/*   Updated: 2022/06/12 18:34:54 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_mlx	*malloc_mlx(char *win_title, t_map *map)
{
	t_mlx	*mlx;

	mlx = NULL;
	mlx = ft_memalloc(sizeof(t_mlx));
	if (!mlx)
		return (NULL);
	mlx->mlxptr = mlx_init();
	mlx->winptr = mlx_new_window(mlx->mlxptr, WIN_WIDTH, WIN_HEIGHT, win_title);
	mlx->image = new_image(mlx);
	mlx->map = map;
	mlx->projection = 1;
	mlx->end = 1;
	mlx->angle = ft_memalloc(sizeof(t_angle));
	if (mlx->image == NULL || mlx->angle == NULL || mlx->map == NULL
		|| mlx->mlxptr == NULL || mlx->winptr == NULL)
		return (NULL);
	mlx->angle->x = 0.52359;
	mlx->angle->y = 0.52359;
	mlx->angle->scale = 16;
	mlx->angle->offsetx = WIN_WIDTH / 2;
	mlx->angle->offsety = WIN_HEIGHT / 2;
	return (mlx);
}

static t_vector	shift_view(t_vector vector, t_mlx *mlx)
{
	if (mlx->projection == 1)
		vector = set_projection_1(vector, mlx);
	else
		vector = set_projection_2_and_0(vector, mlx);
	//printf("5 %f\n", vector.z);
	vector.x *= mlx->angle->scale;
	vector.y *= mlx->angle->scale;
	vector.x += mlx->angle->offsetx;
	vector.y += mlx->angle->offsety;
	//printf("6 %f\n", vector.z);
	return (vector);
}

static void	draw(t_mlx *mlx, t_vector vec1, t_vector vec2)
{
	double		delta_x;
	double		delta_y;

	//printf("1 %f\n", vec1.z);
	vec1 = shift_view(vec1, mlx);
	vec2 = shift_view(vec2, mlx);
	delta_x = calculate_delta(vec1, vec2, 1);
	delta_y = calculate_delta(vec1, vec2, 2);
	if (!cohen_sutherland_lineclip(&vec1, &vec2))
		return ;
	//printf("x %f\n", vec1.z);
	while (((int)(vec1.x - round(vec2.x)) || (int)(vec1.y - round(vec2.y))))
	{
		if (vec1.x > WIN_WIDTH || vec1.y > WIN_HEIGHT
			|| vec1.y < 0 || vec1.x < 0)
			break ;
		put_pixel_in_image(mlx->image,
			(int)round(vec1.x), (int)round(vec1.y), 0xFFFFFF);
		vec1.x += delta_x;
		vec1.y += delta_y;
	}
	if (ft_abs_db(round(vec2.x) - vec1.x) < delta_x
		|| ft_abs_db(round(vec2.y) - vec1.y) < delta_y
		|| (mlx->map->width == 1 && mlx->map->height == 1))
		finish_line_and_one_point(vec1, vec2, mlx);
}

void	render(t_mlx *mlx)
{
	t_vector	vec;
	int			x;
	int			y;

	clear_image(mlx->image);
	y = 0;
	while (y < mlx->map->height)
	{
		x = 0;
		while (x < mlx->map->width)
		{
			vec = vector_list(mlx, x, y);
			if (x + 1 < mlx->map->width)
				draw(mlx, vec, vector_list(mlx, x + 1, y));
			if (y + 1 < mlx->map->height)
				draw(mlx, vec, vector_list(mlx, x, y + 1));
			if (mlx->map->width == 1 && mlx->map->height == 1)
				draw(mlx, vec, vec);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->mlxptr, mlx->winptr, mlx->image->image, 0, 0);
}

void	graphics(t_map *map, char *window_title)
{
	t_mlx	*mlx;

	mlx = malloc_mlx(window_title, map);
	if (mlx == NULL)
		print_error("Error: Cannot initialize mlx");
	render(mlx);
	mlx_key_hook(mlx->winptr, key_event, mlx);
	menu(mlx);
	mlx_loop(mlx->mlxptr);
}
