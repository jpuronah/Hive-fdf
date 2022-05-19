/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:43:13 by jpuronah          #+#    #+#             */
/*   Updated: 2022/05/19 20:27:58 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	printf_error(char *reason)
{
	ft_putendl(reason);
	exit(EXIT_FAILURE);
}

t_mlx	*malloc_mlx(void)
{
	t_mlx		*mlx;

	mlx = (t_mlx *)malloc(sizeof(t_mlx));
	mlx->mlxptr = NULL;
	mlx->winptr = NULL;
	mlx->map = NULL;
	return (mlx);
}


void	get_vectors_from_line(char *line, t_vector *vectors, t_map *map)
{
	int			x;

	x = -1;
	while (*line != '\0' && *line != '\n')
	{
		if (*line >= '0' && *line <= '9')
		{
			vectors->x++;
			vectors->y = map->height;
			vectors->z = *line + '0';
		}
	}
}

t_vector	*malloc_vector()
{
	t_vector *vector;

	vector->x = 0;
	vector->y = 0;
	vector->z = 0;
	return (vector);
}

void	get_vectors(t_mlx *mlx)
{
	t_vector	**vectors;

	vectors = (t_vector **)malloc(sizeof(t_vector) * (mlx->map->height * mlx->map->width + 1));
	//vectors->
	//get_vectors_from_line(line, *vectors, map);
}

int		main(int ac, char **av)
{
	int			fd;
	int			*z;
	t_mlx		*mlx;

	fd = open(av[1], O_RDONLY);
	mlx = malloc_mlx();
	if (ac == 2 && fd > 0)
	{
		mlx->map = read_and_save_map(fd);
		printf("%d, %d\n", mlx->map->width, mlx->map->height);
		//get_vectors(mlx);
	}
	else
		printf_error("error: wrong number of arguments");
	free(mlx->map);
	free(mlx);
	close(fd);
	return (0);
}
