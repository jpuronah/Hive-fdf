/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:27:13 by jpuronah          #+#    #+#             */
/*   Updated: 2022/06/01 12:45:54 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

//This causes leaks cause cant code
void	menu(t_mlx *mlx)
{
	mlx_string_put(mlx->mlxptr, mlx->winptr, 20, 20, WHITE, "Press 'ESC' for EXIT");
	mlx_string_put(mlx->mlxptr, mlx->winptr, 20, 40, WHITE, "Zoom: '1' & '2'");
	mlx_string_put(mlx->mlxptr, mlx->winptr, 20, 55, WHITE, "Move: 'WASD'");
	mlx_string_put(mlx->mlxptr, mlx->winptr, 20, 70, WHITE, "Rotate: Arrow keys");
}

t_mlx	*init_mlx(char *win_title, t_map *map)
{
	t_mlx	*mlx;

	mlx = ft_memalloc(sizeof(t_mlx));
	if (!mlx)
		return (NULL);
	mlx->frame = 0;
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
	mlx->mouse = ft_memalloc(sizeof(t_mouse));
	//free(map->vectors);
	//free(map);
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
	mlx->frame += 1;
	//printf("frame: %d\n", mlx->frame);
	//if (mlx->frame >= 200 && mlx->frame <= 600)
	//	put_object(mlx);
	while (((int)vector1.x != (int)vector2.x || (int)vector1.y != (int)vector2.y))
	{
		if (init_line(mlx, &line, &vector1, &vector2))// || put_background(mlx))
			break ;
	}
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

int		hook_keydown(int key, t_mlx *mlx)
{
	(void)mlx;
	if (key == 65307)
		exit(EXIT_SUCCESS);
	return (0);
}

void	graphics(t_map *map, char *window_title)
{
	t_mlx	*mlx;

	mlx = init_mlx(window_title, map);
	if (mlx == NULL)
		print_error ("Error; Cannot initialize mlx");
	render(mlx);
	menu(mlx);
	mlx->frame++;
	//mlx_key_hook(mlx->winptr, key_event, mlx);
	mlx_key_hook(mlx->winptr, hook_keydown, mlx);
	//mlx_mouse_hook(mlx->winptr, mouse_move, mlx);
	//mlx_hook(mlx->winptr, 5, 0, mouse_move, mlx);
	//mlx_mouse_hook(mlx->winptr, hook_mousedown, mlx);
	//mlx_mouse_hook(mlx->winptr, hook_mouseup, mlx);
	//mlx_mouse_hook(mlx->winptr, hook_mousemove, mlx);
	//mlx_hook(mlx->winptr, 4, 0, hook_mousedown, mlx);
	//mlx_hook(mlx->winptr, 5, 0, hook_mouseup, mlx);
	//mlx_hook(mlx->winptr, 6, 0, hook_mousemove, mlx);
	//menu(mlx);
	mlx_loop(mlx->mlxptr);
}
