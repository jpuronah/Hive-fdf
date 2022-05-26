/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utility.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:16:05 by jpuronah          #+#    #+#             */
/*   Updated: 2022/05/26 11:16:37 by jpuronah         ###   ########.fr       */
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
int		delete_save_and_map(char *save, t_map **map)
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
