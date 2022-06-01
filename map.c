/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 17:02:45 by jpuronah          #+#    #+#             */
/*   Updated: 2022/06/01 16:29:27 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//	Todella kyseenalasia juttuja täällä
//	in English: Very questionable stuff here

static t_map	*init_map(void)
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

static int	get_map_width(char *line)
{
	int		width;
	int		check;
	int		index;
	size_t	len;

	width = 0;
	index = 0;
	len = 0;
	len = ft_countwords(line, ' ');
	printf("%zu\n", len);
	printf("%s\n", line);
	while (len > 0 && line[index] != '\0')// && line[index] != '\n')
	{
		len--;
		check = 0;
		if (line[index] == '-')
			index++;
		while ((line[index] >= '0' && line[index] <= '9'))
		{
			check = 1;
			index++;
		}
		//if (line[index] == ' ')
		//	index++;
		if (check == 1)
			width++;
		index++;
	}
	printf("%d\n", width);
	return (width);
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
	map->vectors = ft_memalloc(sizeof(t_vector) * tmp->width * tmp->height);
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

char	*save_fd_to_array(int fd, t_mlx *mlx)
{
	int			ret;
	char		*line;
	char		*save;

	save = NULL;
	mlx->map = init_map();
	ret = get_next_line(fd, &line);
	while (ret == 1)
	{
		mlx->map->height++;
		if (mlx->map->width == 0)
			mlx->map->width = get_map_width(line);
		save = save_save(save, line);
		ft_strdel(&line);
		ret = get_next_line(fd, &line);
	}
	ft_strdel(&line);
	free(line);
	return (save);
}

void	read_and_save_map(int fd, t_mlx *mlx)
{
	char	*map_array;

	map_array = save_fd_to_array(fd, mlx);
	mlx->map = malloc_map(mlx->map);
	mlx->map = vectors_for_map(map_array, mlx->map);
	free(map_array);
	map_array = NULL;
}
