/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:43:13 by jpuronah          #+#    #+#             */
/*   Updated: 2022/05/20 16:46:07 by jpuronah         ###   ########.fr       */
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

int	main(int ac, char **av)
{
	int			fd;
	t_mlx		*mlx;

	fd = open(av[1], O_RDONLY);
	mlx = malloc_mlx();
	mlx->map = init_map();
	if (ac == 2 && fd > 0)
	{
		mlx->map = read_and_save_map(fd, mlx->map);
		printf("%d, %d\n", mlx->map->width, mlx->map->height);
		int i = 0;
		while (i < (mlx->map->height * mlx->map->width))
		{
			printf("z (%d, %d): %d\n", mlx->map->vectors[i]->x, mlx->map->vectors[i]->y, mlx->map->vectors[i]->z);
			i++;
		}
	}
	else
		printf_error("error: wrong number of arguments");
	free(mlx->map);
	free(mlx);
	close(fd);
	return (0);
}
