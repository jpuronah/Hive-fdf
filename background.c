/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 13:41:23 by jpuronah          #+#    #+#             */
/*   Updated: 2022/05/26 13:41:38 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	put_object(t_mlx *mlx)
{
	int		frame;

	frame = mlx->frame;
	put_pixel_in_image(mlx->image, frame / 2, 120, 0xFFFFFF);
	put_pixel_in_image(mlx->image, frame / 2, 120, 0xFFFFFF);
	return (0);
}

int	put_background(t_mlx *mlx)
{
	int		frame;

	frame = mlx->frame;
	if (frame < 0 || frame >= WIN_WIDTH)
		mlx->frame = 0;
	put_pixel_in_image(mlx->image, frame + -400, 30, 0xFFFFFF);
	put_pixel_in_image(mlx->image, frame + -400, 330, 0xFFFFFF);
	put_pixel_in_image(mlx->image, frame + -200, 30, 0xFFFFFF);
	put_pixel_in_image(mlx->image, frame + -200, 330, 0xFFFFFF);
	put_pixel_in_image(mlx->image, frame, 30, 0xFFFFFF);
	put_pixel_in_image(mlx->image, frame, 330, 0xFFFFFF);
	put_pixel_in_image(mlx->image, frame + 200, 30, 0xFFFFFF);
	put_pixel_in_image(mlx->image, frame + 200, 330, 0xFFFFFF);
	put_pixel_in_image(mlx->image, frame + 400, 30, 0xFFFFFF);
	put_pixel_in_image(mlx->image, frame + 400, 330, 0xFFFFFF);
	put_pixel_in_image(mlx->image, frame + 600, 30, 0xFFFFFF);
	put_pixel_in_image(mlx->image, frame + 600, 330, 0xFFFFFF);
	if (mlx == NULL)
		return (1);
	return (0);
}
