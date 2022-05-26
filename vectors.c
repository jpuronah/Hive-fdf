/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 23:31:04 by jpuronah          #+#    #+#             */
/*   Updated: 2022/05/26 11:15:50 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

t_vector	*init_vector(int x, int y, char *str)
{
	t_vector	*vector;

	vector = NULL;
	vector = malloc(sizeof(t_vector));
	//vector = ft_memalloc(sizeof(t_vector));
	if (vector == NULL)
		return (NULL);
	vector->x = x;
	vector->y = y;
	vector->z = ft_atoi(str);
	vector->color = 0;
	//vector->color = 0xFFFFFF;
	return (vector);
}

t_map *vectors_for_map(char *save, t_map *tmp)
{
	char		**split_save;
	int			x;
	int			y;
	t_map		*map;

	y = 0;
	map = malloc_map(tmp);
	split_save = ft_strsplit(save, ' ');
	if (split_save == NULL)
		delete_save_and_map(save, &map);
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			map->vectors[y * map->width + x] = init_vector(x, y, split_save[x + (y * map->width)]);
			x++;
		}
		y++;
	}
	y = 0;
	while (split_save[y])
	{
		free(split_save[y]);
		y++;
	}
	free(split_save);
	map_depth(map);
	return (map);
}
