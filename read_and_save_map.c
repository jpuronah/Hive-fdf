/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_save_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 17:02:45 by jpuronah          #+#    #+#             */
/*   Updated: 2022/06/12 15:53:15 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	check_width(int width, t_mlx *mlx)
{
	if (mlx->map->width == 0)
		return (width);
	else if (mlx->map->width == width)
		return (width);
	else
		print_error("error: uneven lines");
	return (0);
}

static int	get_map_width(char *line, t_mlx *mlx)
{
	int		width;

	width = 0;
	width = (int)ft_countwords(line, ' ');
	if (check_width(width, mlx))
		return (width);
	return (0);
}

static t_map	*malloc_map(t_map *tmp)
{
	t_map	*map;

	map = ft_memalloc(sizeof(t_map));
	if (map == NULL)
		return (NULL);
	map->width = tmp->width;
	map->height = tmp->height;
	map->vectors = NULL;
	map->vectors = ft_memalloc(sizeof(t_vector)
			* (size_t)tmp->width * (size_t)tmp->height);
	if (map->vectors == NULL)
	{
		ft_memdel((void **)&map);
		return (NULL);
	}
	free(tmp->vectors);
	tmp->vectors = NULL;
	free(tmp);
	tmp = NULL;
	return (map);
}

static char	*save_fd_to_array(int fd, t_mlx *mlx)
{
	int			ret;
	int			content;
	char		*line;
	char		*save;

	save = NULL;
	content = 0;
	ret = get_next_line(fd, &line);
	while (ret == 1)
	{
		content = 1;
		mlx->map->height++;
		mlx->map->width = get_map_width(line, mlx);
		if (line)
			check_line(line, mlx);
		save = save_save(save, line);
		ft_strdel(&line);
		ret = get_next_line(fd, &line);
	}
	if (content)
	{
		ft_strdel(&line);
		line = NULL;
	}
	return (save);
}

void	read_and_save_map(int fd, t_mlx *mlx)
{
	char	*map_array;

	map_array = save_fd_to_array(fd, mlx);
	mlx->map = malloc_map(mlx->map);
	if (map_array && mlx->map)
		mlx->map = vectors_for_map(map_array, mlx->map);
	else
		print_error("error: map_array");
	if (map_array)
		ft_strdel(&map_array);
	map_depth(mlx->map);
}
