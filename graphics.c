/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:27:13 by jpuronah          #+#    #+#             */
/*   Updated: 2022/06/02 18:00:36 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//https://www.quora.com/How-do-you-mathematically-spin-a-square
//https://pbs.twimg.com/media/EePmmJfXoAU9xOn.jpg?name=orig#@troll_lock
//https://pbs.twimg.com/media/EcAQgNBXkAAEMNy.jpg?name=orig#@troll_lock

static t_mlx	*malloc_mlx(char *win_title, t_map *map)
{
	t_mlx	*mlx;

	mlx = ft_memalloc(sizeof(t_mlx));
	if (!mlx)
		return (NULL);
	mlx->mlxptr = mlx_init();
	mlx->winptr = mlx_new_window(mlx->mlxptr, WIN_WIDTH, WIN_HEIGHT, win_title);
	mlx->image = new_image(mlx);
	mlx->map = map;
	mlx->cam = ft_memalloc(sizeof(t_cam));
	if (mlx->image == NULL || mlx->cam == NULL || mlx->map == NULL
		|| mlx->mlxptr == NULL || mlx->winptr == NULL)
		return (NULL);
	mlx->cam->x = 0.5;
	mlx->cam->y = 0.5;
	mlx->cam->scale = 4;
	mlx->cam->offsetx = WIN_WIDTH / 2;
	mlx->cam->offsety = WIN_HEIGHT / 2;
	mlx->cam->spin = 0;
	mlx->max_x = 0;
	mlx->max_y = 0;
	return (mlx);
}

static int	init_line(t_mlx *mlx, t_line *line,
	t_vector *vector1, t_vector *vector2)
{
	//printf("line1: (%d, %d)\n", (int)vector1->x, (int)vector1->y);
	//printf("line2: (%d, %d)\n", (int)vector2->x, (int)vector2->y);
	if (vector1->x < 0 || vector1->x >= WIN_WIDTH || vector1->y < 0
		|| vector1->y >= WIN_HEIGHT || vector2->x < 0 || vector2->x >= WIN_WIDTH
		|| vector2->y < 0 || vector2->y >= WIN_HEIGHT)
		return (1);
	put_pixel_in_image(mlx->image, (int)vector1->x, (int)vector1->y, 0xFFFFFF);
	line->err2 = line->err;
	if (line->err2 > -line->delta_x)
	{
		line->err -= line->delta_y;
		vector1->x += line->sx;
	}
	if (line->err2 < line->delta_y)
	{
		line->err += line->delta_x;
		vector1->y += line->sy;
	}
	return (0);
}

static void	draw(t_mlx *mlx, t_vector vector1, t_vector vector2)
{
	t_line	line;

	/*vector1.x = (int)vector1.x;
	vector2.x = (int)vector2.x;
	vector1.y = (int)vector1.y;
	vector2.y = (int)vector2.y;*/
	line.start = vector1;
	line.stop = vector2;
	line.delta_x = (int)ft_abs((int)vector2.x - (int)vector1.x);
	//line.sx = (int)vector1.x < (int)vector2.x ? 1 : -1;
	if ((int)vector1.x < (int)vector2.x)
		line.sx = 1;
	else
		line.sx = -1;
	line.delta_y = (int)ft_abs((int)vector2.y - (int)vector1.y);
	//line.sy = (int)vector1.y < (int)vector2.y ? 1 : -1;
	if ((int)vector1.y < (int)vector2.y)
		line.sy = 1;
	else
		line.sy = -1;
	//line.err = (line.delta_x > line.delta_y ? line.delta_x : -line.delta_y) / 2;
	if (line.delta_x > line.delta_y)
		line.err = line.delta_x / 2;
	else
		line.err = -line.delta_y / 2;
	while ((int)vector1.x != (int)vector2.x || (int)vector1.y != (int)vector2.y)
	{
		//printf("vector1: (%d, %d) %f\n", (int)vector1.x, (int)vector1.y, vector1.z);
		//printf("vector2: (%d, %d) %f\n", (int)vector2.x, (int)vector2.y, vector2.z);
		if (init_line(mlx, &line, &vector1, &vector2))
			break ;
	}
	if ((int)vector1.x == (int)vector2.x && (int)vector1.y == (int)vector2.y)
	{
		//printf("if vector1: (%d, %d) %f\n", (int)vector1.x, (int)vector1.y, vector1.z);
		//printf("if vector2: (%d, %d) %f\n", (int)vector2.x, (int)vector2.y, vector2.z);
		init_line(mlx, &line, &vector1, &vector2);
	}
}

void	get_max_x_and_y(t_mlx *mlx)
{
	mlx->max_y = mlx->map->vectors[(mlx->map->height * mlx->map->width) - 1]->y;
	mlx->max_x = mlx->map->vectors[(mlx->map->height * mlx->map->width) - 1]->x;
	//mlx->max_y = mlx->map->vectors[mlx->map->height * mlx->map->width]->y * (double)(mlx->map->width - 1) / 2.0f;
	//mlx->max_x = mlx->map->vectors[mlx->map->height * mlx->map->width]->x * (double)(mlx->map->width - 1) / 2.0f;
	mlx->max_x = mlx->max_x * mlx->cam->scale + mlx->cam->offsetx;
	mlx->max_y = mlx->max_y * mlx->cam->scale + mlx->cam->offsety;
	mlx->max_x = mlx->max_x - (mlx->cam->scale * (mlx->map->width / 2.0f));
	mlx->max_y = mlx->max_y - (mlx->cam->scale * (mlx->map->height / 2.0f));
	
}

void	render(t_mlx *mlx)
{
	int			x;
	int			y;
	t_vector	vector;

	get_max_x_and_y(mlx);
	mlx_clear_window(mlx->mlxptr, mlx->winptr);
	reset_image(mlx->image);
	y = 0;
	while (y < mlx->map->height)
	{
		x = 0;
		while (x < mlx->map->width)
		{
			vector = project_vector(get_vector_for_render(mlx->map, x, y), mlx);
			if (x + 1 < mlx->map->width)
				draw(mlx, vector, project_vector
					(get_vector_for_render(mlx->map, x + 1, y), mlx));
			if (y + 1 < mlx->map->height)
				draw(mlx, vector, project_vector
					(get_vector_for_render(mlx->map, x, y + 1), mlx));
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
		print_error ("Error; Cannot initialize mlx");
	render(mlx);
	menu(mlx);
	mlx_key_hook(mlx->winptr, key_event, mlx);
	mlx_loop(mlx->mlxptr);
}
