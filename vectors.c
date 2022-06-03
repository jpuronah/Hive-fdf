/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 23:31:04 by jpuronah          #+#    #+#             */
/*   Updated: 2022/06/03 13:42:44 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

static t_vector	geometry_stuff(t_vector previous, t_cam *r, t_mlx *mlx)
{
	t_vector	vector;
	double		x;
	double		y;
	double		z;

	x = previous.x;
	z = previous.z;
	//printf("cam: %f, %f\n", r->x, r->y);
	if (r->y < -6.2 || r->y > 6.2)
		mlx->cam->y = 0;
	if (r->x < -6.2 || r->x > 6.2)
		mlx->cam->x = 0;
	vector.x = cos(r->y) * x + sin(r->y) * z;
	vector.z = -sin(r->y) * x + cos(r->y) * z;
	y = previous.y;
	//printf("(%f, %f)\n", x, y);
	z = vector.z;
	vector.y = cos(r->x) * y - sin(r->x) * z;
	vector.z = sin(r->x) * y + cos(r->x) * z;
	vector.color = previous.color;
	return (vector);
}

t_vector	get_vector_for_render(t_map *map, int x, int y)
{
	return (*map->vectors[y * map->width + x]);
}

t_vector	project_vector(t_vector vector, t_mlx *mlx)
{
	//printf("inee: %f, %f, %f\n", vector.x, vector.y, vector.z);
	vector.x -= (double)(mlx->map->width - 1) / 2.0f;
	vector.y -= (double)(mlx->map->height - 1) / 2.0f;
	vector.z -= (double)(mlx->map->depth_min + mlx->map->depth_max) / 2.0f;
	//printf("%d, %d, %d\n", mlx->map->width, mlx->map->height, mlx->map->depth_min + mlx->map->depth_max);
	//printf("kesk: %f, %f, %f\n", vector.x, vector.y, vector.z);
	vector = geometry_stuff(vector, mlx->cam, mlx);
	//printf("ulos: %f, %f, %f\n\n", vector.x, vector.y, vector.z);
	vector.x *= mlx->cam->scale;
	vector.y *= mlx->cam->scale;
	vector.x += mlx->cam->offsetx;
	vector.y += mlx->cam->offsety;
	//printf("%f, %f\n", vector.x, vector.y);
	//printf("max_x: %f, max_y %f, (%d, %d)\n", mlx->max_x, mlx->max_y, (int)vector.x, (int)vector.y);
	//mlx->max_x = mlx->max_x - (mlx->cam->scale * (mlx->map->width / 2.0f));
	//mlx->max_y = mlx->max_y - (mlx->cam->scale * (mlx->map->height / 2.0f));
	//printf("max_x: %f, max_y %f, (%d, %d)\n", mlx->max_x, mlx->max_y, (int)vector.x, (int)vector.y);
	//printf("max_x: %f, max_y %f\n", mlx->max_x, mlx->max_y);
	//printf("keski: %f, %f\n", vector.x, vector.y);
	//printf("sum: %f\n", sum);
	
	
	/*printf("helou(%d, %d)\n", (int)vector.x, (int)vector.y);
	if (vector.y < mlx->max_y && vector.x < mlx->max_x)
	{
		printf("vaseylä\n");
		printf("(%d, %d)\n", (int)vector.x, (int)vector.y);
		printf("max_x: %f, max_y %f\n", mlx->max_x, mlx->max_y);
		vector.x += mlx->cam->spin;
		vector.y -= mlx->cam->spin;
	}
	else if (vector.y < mlx->max_y && vector.x >= mlx->max_x)
	{
		printf("oikeylä\n");
		printf("(%d, %d)\n", (int)vector.x, (int)vector.y);
		printf("max_x: %f, max_y %f\n", mlx->max_x, mlx->max_y);
		vector.x += mlx->cam->spin;
		vector.y += mlx->cam->spin;
	}
	else if (vector.y >= mlx->max_y && vector.x >= mlx->max_x)
	{
		printf("oikeala\n");
		printf("(%d, %d)\n", (int)vector.x, (int)vector.y);
		printf("max_x: %f, max_y %f\n", mlx->max_x, mlx->max_y);
		vector.x -= mlx->cam->spin;
		vector.y += mlx->cam->spin;
	}
	else if (vector.y >= mlx->max_y && vector.x < mlx->max_x)
	{
		printf("vaseala\n");
		printf("(%d, %d)\n", (int)vector.x, (int)vector.y);
		printf("max_x: %f, max_y %f\n", mlx->max_x, mlx->max_y);
		vector.x -= mlx->cam->spin;
		vector.y -= mlx->cam->spin;
	}*/


	/*if (vector.y < 360 && vector.x < 640)
	{
		printf("vaseylä\n");
		vector.x += mlx->cam->spin;
		vector.y -= mlx->cam->spin;
	}
	else if (vector.y < 360 && vector.x >= 640)
	{
		printf("oikeylä\n");
		vector.x += mlx->cam->spin;
		vector.y += mlx->cam->spin;
	}
	else if (vector.y >= 360 && vector.x >= 640)
	{
		printf("oikeala\n");
		vector.x -= mlx->cam->spin;
		vector.y += mlx->cam->spin;
	}
	else if (vector.y >= 360 && vector.x < 640)
	{
		printf("vaseala\n");
		vector.x -= mlx->cam->spin;
		vector.y -= mlx->cam->spin;
	}*/

	
	/*if (vector.y < mlx->max_y / 2 && vector.x < mlx->max_x / 2)
	{
		vector.x *= mlx->cam->spin;
		vector.y /= mlx->cam->spin;
	}
	else if (vector.y < mlx->max_y / 2 && vector.x >= mlx->max_x / 2)
	{
		vector.x *= mlx->cam->spin;
		vector.y *= mlx->cam->spin;
	}
	else if (vector.y >= mlx->max_y / 2 && vector.x >= mlx->max_x / 2)
	{
		vector.x /= mlx->cam->spin;
		vector.y *= mlx->cam->spin;
	}
	else if (vector.y >= mlx->max_y / 2 && vector.x < mlx->max_x / 2)
	{
		vector.x /= mlx->cam->spin;
		vector.y /= mlx->cam->spin;
	}*/
	/*printf("pois: %f, %f\n", vector.x, vector.y);
	printf("scale: %d\n", mlx->cam->scale);
	printf("spin: %f\n", mlx->cam->spin);
	printf("cam x & y(%f, %f)\n", mlx->cam->x, mlx->cam->y);
	printf("sum/new sum%f\n", sum / (vector.x + vector.y));
	sum2 = vector.x + vector.y;
	printf("sum: %f\n", sum);
	printf("sum: %f\n", sum2);*/
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
