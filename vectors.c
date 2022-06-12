/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 23:31:04 by jpuronah          #+#    #+#             */
/*   Updated: 2022/06/12 20:06:56 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vector	vector_list(t_mlx *mlx, int x, int y)
{
	t_vector	vector;

	vector = *mlx->map->vectors[y * mlx->map->width + x];
	if (mlx->end == 1)
	{
		vector.x -= (double)(mlx->map->width - 1.0) / 2.0f;
		vector.y -= (double)(mlx->map->height - 1.0) / 2.0f;
		vector.z -= (double)(mlx->map->depth_min + mlx->map->depth_max) / 2.0f;
	}
	if (mlx->end == 2)
	{
		vector.x -= (double)(mlx->map->width - 1.0);
		vector.y -= (double)(mlx->map->height - 1.0);
		vector.z -= (double)(mlx->map->depth_min + mlx->map->depth_max);
	}
	if (mlx->end == 3)
	{
		vector.x -= 0;
		vector.y -= 0;
		vector.z -= 0;
	}
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
	if (vector->z > 2147483647 || vector->z < -2147483648)
		print_error("error: z value outside int scope");
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
	return (map);
}
