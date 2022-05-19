/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 17:02:45 by jpuronah          #+#    #+#             */
/*   Updated: 2022/05/19 17:50:33 by jpuronah         ###   ########.fr       */
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

void	get_map_width(char *line, t_map *map)
{
	int		width;
	int		space;

	width = 0;
	space = 0;
	printf("test\n");
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
	printf("%d\n", width);
	if (map->width > 0)
		if (map->width != width || space != width - 1)
			printf_error("error: inputfile width error");
	map->width = width;
}

t_map	*read_and_save_map(int fd)
{
	int			ret;
	char		*line;
	t_map		*map;

	line = NULL;
	map = init_map();
	ret = get_next_line(fd, &line);
	while (ret == 1)
	{
		//printf("line: %s\n", line);
		map->height++;
		get_map_width(line, map);
		free(line);
		ret = get_next_line(fd, &line);
	}
	return (map);
}
