/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 23:31:04 by jpuronah          #+#    #+#             */
/*   Updated: 2022/06/02 09:06:21 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_vector	geometry_stuff(t_vector p, t_cam *r)
{
	t_vector	vector;
	double		x;
	double		y;
	double		z;

	x = p.x;
	z = p.z;
	vector.x = cos(r->y) * x + sin(r->y) * z;
	vector.z = -sin(r->y) * x + cos(r->y) * z;
	y = p.y;
	z = vector.z;
	vector.y = cos(r->x) * y - sin(r->x) * z;
	vector.z = sin(r->x) * y + cos(r->x) * z;
	vector.color = p.color;
	return (vector);
}

t_vector	get_vector_for_render(t_map *map, int x, int y)
{
	return (*map->vectors[y * map->width + x]);
}

t_vector	project_vector(t_vector vector, t_mlx *mlx)
{
	vector.x -= (double)(mlx->map->width - 1) / 2.0f;
	vector.y -= (double)(mlx->map->height - 1) / 2.0f;
	vector.z -= (double)(mlx->map->depth_min + mlx->map->depth_max) / 2.0f;
	vector = geometry_stuff(vector, mlx->cam);
	vector.x *= mlx->cam->scale;
	vector.y *= mlx->cam->scale;
	vector.x += mlx->cam->offsetx;
	vector.y += mlx->cam->offsety;
	return (vector);
}

static t_vector	*init_vector(int x, int y, char *str)
{
	t_vector	*vector;

	vector = NULL;
	vector = ft_memalloc(sizeof(t_vector));
	if (vector == NULL)
		return (NULL);
	vector->x = x;
	vector->y = y;
	if (str != NULL)
		vector->z = ft_atoi(str);
	vector->color = 0;
	return (vector);
}

t_map	*vectors_for_map(char *save, t_map *map)
{
	char		**split_save;
	int			x;
	int			y;

	split_save = ft_strsplit(save, ' ');
	if (split_save == NULL)
		delete_save_and_map(save, &map);
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			map->vectors[y * map->width + x]
				= init_vector(x, y, split_save[x + (y * map->width)]);
			x++;
		}
		y++;
	}
	y = 0;
	while (split_save[y])
		free(split_save[y++]);
	free(split_save);
	map_depth(map);
	return (map);
}
