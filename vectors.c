/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 23:31:04 by jpuronah          #+#    #+#             */
/*   Updated: 2022/05/25 16:40:27 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


void		find_depth(t_map *map)
{
	int			min;
	int			max;
	t_vector	v;
	t_vector	cur;

	min = 0;
	max = 0;
	v.y = 0;
	while (v.y < map->height)
	{
		v.x = 0;
		while (v.x < map->width)
		{
			//printf("looppi\n");
			cur = *map->vectors[(int)v.y * map->width + (int)v.x];
			//printf("%d (%d, %d)\n", cur.z, cur.x, cur.y);
			if (cur.z < min)
				min = cur.z;
			if (cur.z > max)
				max = cur.z;
			v.x++;
		}
		v.y++;
	}
	map->depth_min = min;
	map->depth_max = max;
}

//Ei hajuu onks tää mintis
static int	cleanup(char *save, t_map **map)
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
		cleanup(save, &map);
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
	find_depth(map);
	return (map);
}
