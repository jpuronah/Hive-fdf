/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 17:02:45 by jpuronah          #+#    #+#             */
/*   Updated: 2022/05/23 17:30:20 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	*init_map(void)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	map->width = 0;
	map->height = 0;
	map->vectors = NULL;
	return (map);
}

static void	get_map_width(char *line, t_map *map)
{
	int		width;
	int		space;

	width = 0;
	space = 0;
	map->height++;
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

static char	*save_save(char *save, char *line)
{
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	if (save && line)
		tmp = ft_strjoin(save, line);
	else
		tmp = ft_strdup(line);
	if (tmp)
		tmp2 = ft_strjoin(tmp, " ");
	if (save)
		free(save);
	if (line)
		free(line);
	//free(tmp);
	//free(tmp2);
	return (tmp2);
}

t_map	*malloc_map(t_map *tmp)
{
	t_map	*map;

	map = ft_memalloc(sizeof(t_map));
	if (map == NULL)
		return (NULL);
	map->width = tmp->width;
	map->height = tmp->height;
	map->vectors = (t_vector **)malloc(sizeof(t_vector) * tmp->width * tmp->height);
	if (map->vectors == NULL)
	{
		ft_memdel((void **)&map);
		return (NULL);
	}
	free(tmp);
	return (map);
}

t_map	*read_and_save_map(int fd, t_map *map)
{
	int			ret;
	char		*line;
	char		*save;
	char		*tmp;

	tmp = NULL;
	save = NULL;
	ret = get_next_line(fd, &line);
	while (ret == 1)
	{
		get_map_width(line, map);
		tmp = save_save(save, line);
		save = (char *)malloc(sizeof(char) * (map->height * map->width + 1));
		save = ft_strdup(tmp);
		free(tmp);
		ret = get_next_line(fd, &line);
	}
	printf("map: \n");
	map = malloc_map(map);
	map = vectors_for_map(save, map);
	graphics(map, "Title");
	free(save);
	return (map);
}
