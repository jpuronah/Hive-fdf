/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extras.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 20:57:27 by jpuronah          #+#    #+#             */
/*   Updated: 2022/06/05 20:57:38 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_max_x_and_y(t_mlx *mlx)
{
	mlx->max_y = mlx->map->vectors[(mlx->map->height * mlx->map->width) - 1]->y;
	mlx->max_x = mlx->map->vectors[(mlx->map->height * mlx->map->width) - 1]->x;
	mlx->max_x = mlx->max_x * mlx->cam->scale + mlx->cam->offsetx;
	mlx->max_y = mlx->max_y * mlx->cam->scale + mlx->cam->offsety;
	mlx->max_x = mlx->max_x - (mlx->cam->scale * (mlx->map->width / 2.0f));
	mlx->max_y = mlx->max_y - (mlx->cam->scale * (mlx->map->height / 2.0f));
}
