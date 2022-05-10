/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 13:54:17 by jpuronah          #+#    #+#             */
/*   Updated: 2022/04/28 15:08:13 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		get_dots_from_line(char *line, t_fdf **matrix_of_dots, int y)
{
	char	**dots;
	int		x;

	dots = ft_strsplit(line, ' ');
	x = 0;
	while (dots[x])
	{
		matrix_of_dots[y][x].z = ft_atoi(dots[x]);
		matrix_of_dots[y][x].x = x;
		matrix_of_dots[y][x].y = y;
		matrix_of_dots[y][x].is_last = 0;
		free(dots[x++]);
	}
	free(dots);
	free(line);
	matrix_of_dots[y][--x].is_last = 1;
	return (x);
}

t_fdf	**memmory_allocation(char *file_name)
{
	t_fdf	**new;
	int		x;
	int		y;
	int		fd;
	char	*line;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		print_error("error: could not open the file");
	get_next_line(fd, &line);
	x = (int)ft_countwords(line, ' ');
	y = 0;
	while (fd > 0)
	{
		y++;
		free(line);
		fd = get_next_line(fd, &line);
	}
	free(line);
	y++;
	new = (t_fdf **)malloc(sizeof(t_fdf *) * ((size_t)y + 1));
	while (y > 0)
		new[--y] = (t_fdf *)malloc(sizeof(t_fdf) * ((size_t)x + 1));
	close(fd);
	return (new);
}

t_fdf	**read_file(char	*file_name)
{
	t_fdf	**matrix_of_dots;
	int		y;
	int		fd;
	char	*line;

	matrix_of_dots = memmory_allocation(file_name);
	fd = open(file_name, O_RDONLY);
	y = 0;
	while (get_next_line(fd, &line) > 0)
		get_dots_from_line(line, matrix_of_dots, y++);
	
	free(line);
	matrix_of_dots[y] = NULL;
	close(fd);
	return(matrix_of_dots);
}