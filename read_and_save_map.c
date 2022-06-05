/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_save_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 17:02:45 by jpuronah          #+#    #+#             */
/*   Updated: 2022/06/05 20:53:29 by jpuronah         ###   ########.fr       */
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
	len = ft_countwords(line, ' ');
	while (len > 0 && line[index] != '\0')
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
		while (line[index] == ' ')
			index++;
		if (check == 1)
			width++;
	}
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
	int			file_has_content;
	char		*line;
	char		*save;

	file_has_content = 0;
	save = NULL;
	mlx->map = init_map();
	ret = get_next_line(fd, &line);
	while (ret == 1)
	{
		file_has_content = 1;
		mlx->map->height++;
		if (mlx->map->width == 0)
			mlx->map->width = get_map_width(line);
		save = save_save(save, line);
		ft_strdel(&line);
		ret = get_next_line(fd, &line);
	}
	if (file_has_content == 1)
	{
		ft_strdel(&line);
		free(line);
	}
	else
		print_error("error: empty file OR directory");
	return (save);
}

void	check_map_array(char *array)
{
	int		digit;
	int		space;
	int		sign;
	int		index;

	digit = 0;
	space = 0;
	sign = 0;
	index = 0;
	while (array[index] != '\0')
	{
		if (array[index] == ' ')
			space = 1;
		else if (ft_isdigit(array[index]) == 1)
			digit = 1;
		else if (array[index] == '-')
			sign = 0;
		else
			print_error("error: input file character error");
		++index;
	}
	if (digit == 0 || space == 0)
		print_error("error: input file character error");
}

void	read_and_save_map(int fd, t_mlx *mlx)
{
	char	*map_array;

	map_array = save_fd_to_array(fd, mlx);
	check_map_array(map_array);
	mlx->map = malloc_map(mlx->map);
	mlx->map = vectors_for_map(map_array, mlx->map);
	free(map_array);
	map_array = NULL;
}
