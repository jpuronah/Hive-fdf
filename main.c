/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:43:13 by jpuronah          #+#    #+#             */
/*   Updated: 2022/06/12 14:57:13 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_error(char *reason)
{
	ft_putendl(reason);
	exit(EXIT_FAILURE);
}

static t_mlx	*init_mlx(void)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)malloc(sizeof(t_mlx));
	mlx->mlxptr = NULL;
	mlx->winptr = NULL;
	mlx->map = init_map();
	mlx->angle = NULL;
	mlx->image = NULL;
	mlx->projection = 1;
	return (mlx);
}

int	main(int ac, char **av)
{
	t_mlx		*mlx;
	int			fd;

	mlx = init_mlx();
	fd = open(av[1], O_RDONLY);
	if (ac == 2 && fd > 0)
		read_and_save_map(fd, mlx);
	else
	{
		if (fd < 0)
			print_error("usage: ./fdf <inputfile>");
		else
			print_error("error: wrong number of arguments");
	}
	close(fd);
	graphics(mlx->map, av[1]);
	return (0);
}
