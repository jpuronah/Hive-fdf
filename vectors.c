/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 23:31:04 by jpuronah          #+#    #+#             */
/*   Updated: 2022/05/20 17:11:37 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

	//printf("getvector: %d, %d, %s\n", x, y, str);
	vector = ft_memalloc(sizeof(t_vector));
	if (vector == NULL)
		return (NULL);
	vector->x = x;
	vector->y = y;
	vector->z = ft_atoi(str);
	//vector->color = 0xFFFFFF;
	return (vector);
}

t_map *vectors_for_map(char *save, t_map *map)
{
	char		**split_save;
	int			x;
	int			y;
	int			xy;

	y = 0;
	split_save = ft_strsplit(save, ' ');
	if (split_save == NULL)
		cleanup(save, &map);
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			xy = x + (y * map->width);
			map->vectors[y * map->width + x] = init_vector(x, y, split_save[xy]);
			x++;
		}
		y++;
	}
	//map_depth(*map);
	//fill_colors(*map);
	ft_memdel((char *)split_save);
	save = NULL;
	return (map);
}
