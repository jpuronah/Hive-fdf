/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utility.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:16:05 by jpuronah          #+#    #+#             */
/*   Updated: 2022/06/10 12:21:50 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	*init_map(void)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	map->width = 0;
	map->height = 0;
	map->depth_max = 0;
	map->depth_min = 0;
	map->vectors = NULL;
	return (map);
}

void	check_line(char *line, t_mlx *mlx)
{
	int	digit;
	int	space;

	space = 0;
	digit = 0;
	while (*line != '\0')
	{
		if (*line == ' ')
			space = 1;
		else if (ft_isdigit(*line) == 1)
			digit = 1;
		else if (*line == '-')
			digit += 0;
		else if (*line == ',')
			while (*line != ' ')
				line++;
		else
			print_error("error: unknown character");
		++line;
	}
	if (digit == 0 || (space == 0 && mlx->map->width > 1))
		print_error("error: map error");
}

void	map_depth(t_map *map)
{
	int		x;
	int		y;
	int		depth;
	int		min;
	int		max;

	min = 2147483647;
	max = -2147483648;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			depth = (int)map->vectors[y * map->width + x]->z;
			if (depth < min)
				min = depth;
			if (depth > max)
				max = depth;
			x++;
		}
		y++;
	}
	map->depth_max = max;
	map->depth_min = min;
}

char	*save_save(char *save, char *line)
{
	char		*tmp;
	char		*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	tmp = ft_strdup(line);
	if (tmp == NULL)
		return (NULL);
	if (save == NULL)
	{
		save = ft_strjoin(tmp, " ");
		ft_strdel(&tmp);
	}
	else
	{
		tmp2 = save;
		save = ft_strjoin(tmp2, tmp);
		ft_strdel(&tmp);
		ft_strdel(&tmp2);
		tmp2 = save;
		save = ft_strjoin(tmp2, " ");
		ft_strdel(&tmp);
		ft_strdel(&tmp2);
	}
	return (save);
}

int	delete_save_and_map(char *save, t_map **map)
{
	if (save)
		save = NULL;
	if (map && *map)
	{
		ft_memdel((void **)&(*map)->vectors);
		ft_memdel((void **)map);
	}
	print_error("error: can not split map_array");
	return (0);
}
