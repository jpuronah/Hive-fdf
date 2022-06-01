/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:12:21 by jpuronah          #+#    #+#             */
/*   Updated: 2022/06/01 18:52:50 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	menu(t_mlx *mlx)
{
	mlx_string_put(mlx->mlxptr, mlx->winptr, 20, 20,
		WHITE, "Press 'ESC' for EXIT");
	mlx_string_put(mlx->mlxptr, mlx->winptr, 20, 40,
		WHITE, "Move: 'WASD' / 'wasd'");
	mlx_string_put(mlx->mlxptr, mlx->winptr, 20, 60,
		WHITE, "Zoom: '+' & '-'");
	mlx_string_put(mlx->mlxptr, mlx->winptr, 20, 80,
		WHITE, "Rotate: ARROW KEYS");
}

int	key_event(int key, t_mlx *mlx)
{
	if (key == 65307)
		exit(EXIT_SUCCESS);
	if (key == '+')
		mlx->cam->scale = mlx->cam->scale + 1;
	if (key == '-')
		mlx->cam->scale = mlx->cam->scale - 1;
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
	render(mlx);
	menu(mlx);
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

/*
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
*/