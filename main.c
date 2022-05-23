/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:43:13 by jpuronah          #+#    #+#             */
/*   Updated: 2022/05/23 17:11:06 by jpuronah         ###   ########.fr       */
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
	t_map		*map;

	fd = open(av[1], O_RDONLY);
	mlx = malloc_mlx();
	map = init_map();
	if (ac == 2 && fd > 0)
	{
		map = read_and_save_map(fd, map);
		//graphics(map, av[1]);
	}
	else
		printf_error("error: wrong number of arguments");
	int	i = 0;
	while (map->vectors[i] != NULL)
		free(map->vectors[i++]);
	free(map->vectors);
	free(map);
	free(mlx);
	close(fd);
	return (0);
}
