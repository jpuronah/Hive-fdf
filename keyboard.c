/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:12:21 by jpuronah          #+#    #+#             */
/*   Updated: 2022/06/12 20:26:16 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	menu(t_mlx *mlx)
{
	mlx_string_put(mlx->mlxptr, mlx->winptr, 20, 20,
		WHITE, "Press 'ESC' to EXIT PROGRAM");
	mlx_string_put(mlx->mlxptr, mlx->winptr, 20, 40,
		WHITE, "Switch projections: 1 / 2 / 3");
	mlx_string_put(mlx->mlxptr, mlx->winptr, 20, 60,
		WHITE, "Zoom: + / -");
	mlx_string_put(mlx->mlxptr, mlx->winptr, 20, 80,
		WHITE, "Movement: 'WASD'");
	mlx_string_put(mlx->mlxptr, mlx->winptr, 20, 100,
		WHITE, "Movement x10: Arrow keys");
	mlx_string_put(mlx->mlxptr, mlx->winptr, 20, 120,
		WHITE, "Change start point: 8 / 9 / 0");
}

static int	exit_fdf(t_mlx *mlx)
{
	delete_image(mlx, mlx->image);
	mlx_destroy_window(mlx->mlxptr, mlx->winptr);
	exit (EXIT_SUCCESS);
}

static void	set_angle(int key, t_mlx *mlx)
{
	if (key == 18)
	{
		mlx->projection = 1;
		mlx->angle->x = 0.52359;
		mlx->angle->y = 0.52359;
	}
	if (key == 19)
	{
		mlx->projection = 2;
		mlx->angle->x = 0.52359;
		mlx->angle->y = 0.52359;
	}
	if (key == 20)
	{
		mlx->projection = 0;
		mlx->angle->x = 0.52359;
		mlx->angle->y = 0.52359;
	}
}

static void	more_events(int key, t_mlx *mlx)
{
	if (mlx->angle->scale < 1000)
		if (key == 24)
			mlx->angle->scale += 1;
	if (mlx->angle->scale > 1)
		if (key == 27)
			mlx->angle->scale -= 1;
	if (key == 15)
	{
		mlx->projection = 1;
		mlx->end = 1;
		mlx->angle->x = 0.52359;
		mlx->angle->y = 0.52359;
		mlx->angle->scale = 16;
		mlx->angle->offsetx = WIN_WIDTH / 2;
		mlx->angle->offsety = WIN_HEIGHT / 2;
	}
	if (key == 28)
		mlx->end = 2;
	if (key == 25)
		mlx->end = 1;
	if (key == 29)
		mlx->end = 3;
	if (mlx->end < 1 || mlx->end > 3)
		mlx->end = 2;
}

int	key_event(int key, t_mlx *mlx)
{
	if (key == 53)
		exit_fdf(mlx);
	set_angle(key, mlx);
	if (key == 13)
		mlx->angle->offsety -= 15;
	if (key == 1)
		mlx->angle->offsety += 15;
	if (key == 2)
		mlx->angle->offsetx += 15;
	if (key == 0)
		mlx->angle->offsetx -= 15;
	if (key == 126)
		mlx->angle->offsety -= 150;
	if (key == 125)
		mlx->angle->offsety += 150;
	if (key == 124)
		mlx->angle->offsetx += 150;
	if (key == 123)
		mlx->angle->offsetx -= 150;
	more_events(key, mlx);
	render(mlx);
	menu(mlx);
	return (0);
}
