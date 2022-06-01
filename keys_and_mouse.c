/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_and_mouse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:12:21 by jpuronah          #+#    #+#             */
/*   Updated: 2022/06/01 14:46:01 by jpuronah         ###   ########.fr       */
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

int	key_event(int key, t_mlx *mlx)
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
	render(mlx);
	menu(mlx);
	return (0);
}
