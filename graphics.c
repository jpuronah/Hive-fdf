/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:27:13 by jpuronah          #+#    #+#             */
/*   Updated: 2022/05/25 18:15:55 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	free_and_exit(int key, t_mlx *mlx)
{
	int	i;

	i = 0;
	if (key == XK_Escape)
	{
		while (mlx->map->vectors[i])
		{
			free(mlx->map->vectors[i]);
			mlx->map->vectors[i]->x = 0;
			mlx->map->vectors[i]->y = 0;
			mlx->map->vectors[i]->z = 0;
			i++;
		}
		free(mlx->map->vectors);
		mlx->map->height = 0;
		mlx->map->width = 0;
		//free(mlx->mlxptr);
		//free(mlx->winptr);
		free(mlx->map);
		mlx->map = NULL;
		free(mlx);
		mlx = NULL;
		exit(EXIT_SUCCESS);
	}
}

t_vector	get_vector_for_render(t_map *map, int x, int y)
{
	/*printf("(%d, ", map->vectors[y * map->width + x]->x);
	printf("%d): ", map->vectors[y * map->width + x]->y);
	printf("%d\n", map->vectors[y * map->width + x]->z);*/
	return (*map->vectors[y * map->width + x]);
}

t_vector	geometry_stuff(t_vector p, t_cam *r)
{
	t_vector	v;
	double		x;
	double		y;
	double		z;

	x = p.x;
	z = p.z;
	v.x = cos(r->y) * x + sin(r->y) * z;
	v.z = -sin(r->y) * x + cos(r->y) * z;
	y = p.y;
	z = v.z;
	v.y = cos(r->x) * y - sin(r->x) * z;
	v.z = sin(r->x) * y + cos(r->x) * z;
	v.color = p.color;
	return (v);
}

t_vector	project_vector(t_vector v, t_mlx *mlx)
{
	v.x -= (double)(mlx->map->width - 1) / 2.0f;
	v.y -= (double)(mlx->map->height - 1) / 2.0f;
	v.z -= (double)(mlx->map->depth_min + mlx->map->depth_max) / 2.0f;
	//printf("proje z: %d\n", v.z);
	v = geometry_stuff(v, mlx->cam);
	v.x *= mlx->cam->scale;
	v.y *= mlx->cam->scale;
	v.x += mlx->cam->offsetx;
	v.y += mlx->cam->offsety;
	return (v);
}

t_mlx	*init_mlx(char *win_title, t_map *map)
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
	mlx->cam->x = 0.5;
	mlx->cam->y = 0.5;
	mlx->cam->scale = 32;
	mlx->cam->offsetx = WIN_WIDTH / 2;
	mlx->cam->offsety = WIN_HEIGHT / 2;
	//free(map->vectors);
	//free(map);

	//mlx->mouse = ft_memalloc(sizeof(t_mouse));
	return (mlx);
}

static int	init_line(t_mlx *mlx, t_line *l, t_vector *vector1, t_vector *vector2)
{
	if (vector1->x < 0 || vector1->x >= WIN_WIDTH || vector1->y < 0 || vector1->y >= WIN_HEIGHT
		|| vector2->x < 0 || vector2->x >= WIN_WIDTH || vector2->y < 0 || vector2->y >= WIN_HEIGHT)
		return (1);
	put_pixel_in_image(mlx->image, (int)vector1->x, (int)vector1->y, 0xFFFFFF);
	l->err2 = l->err;
	if (l->err2 > -l->delta_x)
	{
		l->err -= l->delta_y;
		vector1->x += l->sx;
	}
	if (l->err2 < l->delta_y)
	{
		l->err += l->delta_x;
		vector1->y += l->sy;
	}
	return (0);
}

static void		draw(t_mlx *mlx, t_vector vector1, t_vector vector2)
{
	t_line	line;

	vector1.x = (int)vector1.x;
	vector2.x = (int)vector2.x;
	vector1.y = (int)vector1.y;
	vector2.y = (int)vector2.y;
	line.start = vector1;
	line.stop = vector2;
	// if joku menee mäpist ulos nii return nolla
	line.delta_x = (int)ft_abs((int)vector2.x - (int)vector1.x);
	line.sx = (int)vector1.x < (int)vector2.x ? 1 : -1;
	line.delta_y = (int)ft_abs((int)vector2.y - (int)vector1.y);
	line.sy = (int)vector1.y < (int)vector2.y ? 1 : -1;
	line.err = (line.delta_x > line.delta_y ? line.delta_x : -line.delta_y) / 2;
	while (((int)vector1.x != (int)vector2.x || (int)vector1.y != (int)vector2.y))
		if (init_line(mlx, &line, &vector1, &vector2))
			break ;
}

void	render(t_mlx *mlx)
{
	int			x;
	int			y;
	t_vector	vector;

	reset_image(mlx->image);
	y = 0;
	while (y < mlx->map->height)
	{
		x = 0;
		while (x < mlx->map->width)
		{
			vector = project_vector(get_vector_for_render(mlx->map, x, y), mlx);
			if (x + 1 < mlx->map->width)
				draw(mlx, vector, project_vector(get_vector_for_render(mlx->map, x + 1, y), mlx));
			if (y + 1 < mlx->map->height)
				draw(mlx, vector, project_vector(get_vector_for_render(mlx->map, x, y + 1), mlx));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->mlxptr, mlx->winptr, mlx->image->image, 0, 0);
}

int		key_event(int key, t_mlx *mlx)
{
	(void)mlx;

	printf("%d\n", key);
	if (key == XK_Escape)
		free_and_exit(key, mlx);
	if (ft_isdigit(key) == 1)
	{
		if (key == '1')
			mlx->cam->scale = mlx->cam->scale + 1;
		if (key == '2')
			mlx->cam->scale = mlx->cam->scale - 1;
		//render(mlx);
		//printf("%d\n", i);
	}
	printf("%f, %f\n", mlx->cam->offsetx, mlx->cam->offsety);
	if (key == 'w')
		mlx->cam->offsety -= 10;
	if (key == 'a')
		mlx->cam->offsetx -= 10;
	if (key == 's')
		mlx->cam->offsety += 10;
	if (key == 'd')
		mlx->cam->offsetx += 10;

	if (key == 65362)
		mlx->cam->x += 0.1;
	if (key == 65361)
		mlx->cam->y -= 0.1;
	if (key == 65364)
		mlx->cam->x -= 0.1;
	if (key == 65363)
		mlx->cam->y += 0.1;
	render(mlx);
	return (0);
}

void	graphics(t_map *map, char *window_title)
{
	t_mlx	*mlx;

	mlx = init_mlx(window_title, map);
	if (mlx == NULL)
		printf_error ("Error; Cannot initialize mlx");
	mlx_key_hook(mlx->winptr, key_event, mlx);
	mlx_string_put(mlx->mlxptr, mlx->winptr, 20, 20, WHITE, "Press 'ESC' for EXIT");
	render(mlx);
	mlx_loop(mlx->mlxptr);
}
