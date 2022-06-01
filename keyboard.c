/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:12:21 by jpuronah          #+#    #+#             */
/*   Updated: 2022/06/01 16:03:34 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	hook_keydown(int key, t_mlx *mlx)
{
	(void)mlx;
	if (key == 65307)
		exit(EXIT_SUCCESS);
	return (0);
}

/*
int		key_event(int key, t_mlx *mlx)
{
	(void)mlx;

	if (key == XK_Escape)
		free_and_exit(key, mlx);
	if (ft_isdigit(key) == 1)
	{
		if (key == '1')
			mlx->cam->scale = mlx->cam->scale + 1;
		if (key == '2')
			mlx->cam->scale = mlx->cam->scale - 1;
		//render(mlx);
		//printf("%d\n", i);
	}
	if (key == 'w')
		mlx->cam->offsety -= 10;
	if (key == 'a')
		mlx->cam->offsetx -= 10;
	if (key == 's')
		mlx->cam->offsety += 10;
	if (key == 'd')
		mlx->cam->offsetx += 10;

	if (key == 65362)
		mlx->cam->x += 0.1;
	if (key == 65361)
		mlx->cam->y -= 0.1;
	if (key == 65364)
		mlx->cam->x -= 0.1;
	if (key == 65363)
		mlx->cam->y += 0.1;
	if (key == 'o')
	{
		mlx->map->depth_max /= 2;
		mlx->map->depth_min /= 2;
	}
	if (key == 'p')
	{
		mlx->map->depth_max += 10;
		mlx->map->depth_min += 10;
	}
	render(mlx);
	menu(mlx);
	return (0);
}*/

int	key_event(int key, t_mlx *mlx)
{
	if (key == 65307)
		exit(EXIT_SUCCESS);
	else if (key == '0')
	{
		mlx->cam->x = 0;
		mlx->cam->y = 0;
		mlx->cam->offsetx = WIN_WIDTH / 2;
		mlx->cam->offsety = WIN_HEIGHT / 2;
	}
	if (key == '1')
	{
		mlx->cam->x = 0.5;
		mlx->cam->y = 0.5;
		mlx->cam->offsetx = WIN_WIDTH / 2;
		mlx->cam->offsety = WIN_HEIGHT / 2;
	}
	if (key == '2')
	{
		mlx->cam->x = 10;
		mlx->cam->y = 10;
		mlx->cam->offsetx = WIN_WIDTH / 2;
		mlx->cam->offsety = WIN_HEIGHT / 2;
	}
	if (key == '+')
		mlx->cam->scale = mlx->cam->scale + 1;
	if (key == '-')
		mlx->cam->scale = mlx->cam->scale - 1;
	render(mlx);
	menu(mlx);
	return (0);
}
