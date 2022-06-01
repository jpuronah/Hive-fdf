/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 17:02:45 by jpuronah          #+#    #+#             */
/*   Updated: 2022/06/01 12:26:21 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//	Todella kyseenalasia juttuja täällä
//	in English: Very questionable stuff here

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
	while (len > 0 && line[index] != '\0' && line[index] != '\n')
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
		if (check == 1)
			width++;
		index++;
	}
	return (width);
}

t_map	*malloc_map(t_map *tmp)
{
	t_map	*map;

	map = ft_memalloc(sizeof(t_map));
	if (map == NULL)
		return (NULL);
	map->width = tmp->width;
	map->height = tmp->height;
	map->param = tmp->param;
	map->vectors = NULL;
	map->vectors = (t_vector **)malloc(sizeof(t_vector) * tmp->width * tmp->height);
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
	char		*tmp;
	char		*tmp2;

	tmp = NULL;
	save = NULL;
	mlx->map = init_map();
	ret = get_next_line(fd, &line);
	while (ret == 1)
	{
		mlx->map->height++;
		mlx->map->width = get_map_width(line);
		tmp = ft_strdup(line);
		if (tmp == NULL)
			return (NULL);
		if (save == NULL)
		{
			save = ft_strjoin(tmp, " ");
			free(tmp);
			tmp = NULL;
		}
		else
		{
			tmp2 = save;
			save = ft_strjoin(tmp2, tmp);
			free(tmp);
			tmp = NULL;
			free(tmp2);
			tmp2 = NULL;
			tmp2 = save;
			save = ft_strjoin(tmp2, " ");
			free(tmp2);
			tmp2 = NULL;
		}
		ft_strdel(&line);
		ret = get_next_line(fd, &line);
	}
	//printf("%s\n", save);
	free(line);
	//exit(EXIT_SUCCESS);
	return (save);
}

void	read_and_save_map(int fd, char *title, t_mlx *mlx)
{
	char	*map_array;

	map_array = save_fd_to_array(fd, mlx);
	//check_map_array(map_array, mlx);
	//mlx->map = malloc_map2(map_array);
	mlx->map = malloc_map(mlx->map);
	mlx->map = vectors_for_map(map_array, mlx->map);
	graphics(mlx->map, title);
	printf("%s\n", title);
	close(fd);
	exit(EXIT_SUCCESS);
}
