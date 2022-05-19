/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 17:02:45 by jpuronah          #+#    #+#             */
/*   Updated: 2022/05/19 23:32:03 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	*malloc_map(int width, int height)
{
	t_map	*map;

	map = ft_memalloc(sizeof(t_map));
	if (map == NULL)
		return (NULL);
	map->width = width;
	map->height = height;
	map->vectors = ft_memalloc(sizeof(t_vector *) * width * height);
	if (map->vectors == NULL)
	{
		ft_memdel((void **)&map);
		return (NULL);
	}
	return (map);
}

t_map	*init_map(void)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	map->width = 0;
	map->height = 0;
	map->vectors = NULL;
	return (map);
}

void	get_map_width(char *line, t_map *map)
{
	int		width;
	int		space;

	width = 0;
	space = 0;
	while (*line != '\0' && *line != '\n')
	{
		if (*line >= '0' && *line <= '9')
			width++;
		else if (*line == ' ')
			space++;
		else if ((*line != 0 && *line != '\n'))
			printf_error("error: inputfile character error");
		line++;
	}
	if (map->width > 0)
		if (map->width != width || space != width - 1)
			printf_error("error: inputfile width error");
	map->width = width;
}

char	*save_save(char *save, char *line)
{
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	tmp = ft_strjoin(save, line);
	tmp2 = ft_strjoin(tmp, " ");
	return (tmp2);
}

t_map	*read_and_save_map(int fd)
{
	int			ret;
	char		*line;
	char		*save;
	t_map		*map;

	map = init_map();
	ret = get_next_line(fd, &line);
	save = (char *)malloc(sizeof(char));
	while (ret == 1)
	{
		map->height++;
		get_map_width(line, map);
		save = save_save(save, line);
		free(line);
		ret = get_next_line(fd, &line);
	}
	map = malloc_map(map->width, map->height);
	map->vectors = get_vectors(save);
	return (map);
}