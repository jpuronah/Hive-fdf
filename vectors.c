/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 23:31:04 by jpuronah          #+#    #+#             */
/*   Updated: 2022/05/25 18:11:21 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		map_depth(t_map *map)
{
	int			min;
	int			max;
	t_vector	vector;
	t_vector	current;

	min = 0;
	max = 0;
	vector.y = 0;
	while (vector.y < map->height)
	{
		vector.x = 0;
		while (vector.x < map->width)
		{
			current = *map->vectors[(int)vector.y * map->width + (int)vector.x];
			if (current.z < min)
				min = current.z;
			if (current.z > max)
				max = current.z;
			vector.x++;
		}
		vector.y++;
	}
	map->depth_min = min;
	map->depth_max = max;
}

//Ei hajuu onks tää mintis
static int	delete_save_and_map(char *save, t_map **map)
{
	if (save)
		save = NULL;
	if (map && *map)
	{
		ft_memdel((void **)&(*map)->vectors);
		ft_memdel((void **)map);
	}
	return (0);
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
