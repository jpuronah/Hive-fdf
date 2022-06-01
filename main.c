/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:43:13 by jpuronah          #+#    #+#             */
/*   Updated: 2022/06/01 11:37:31 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_error(char *reason)
{
	ft_putendl(reason);
	exit(EXIT_FAILURE);
}

t_mlx	*init_mlx2(void)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)malloc(sizeof(t_mlx));
	mlx->mlxptr = NULL;
	mlx->winptr = NULL;
	mlx->map = NULL;
	mlx->cam = NULL;
	mlx->image = NULL;
	mlx->mouse = NULL;
	mlx->frame = 0;
	return (mlx);
}

int	main(int ac, char **av)
{
	int			fd;
	t_mlx	*mlx;

	mlx = init_mlx2();
	fd = open(av[1], O_RDONLY);
	if (ac == 2 && fd > 0)
		read_and_save_map(fd, av[1], mlx);
	else
		print_error("error: wrong number of arguments");
	return (0);
}
