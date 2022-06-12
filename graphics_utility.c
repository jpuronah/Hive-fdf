/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_utility.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 15:17:52 by jpuronah          #+#    #+#             */
/*   Updated: 2022/06/12 20:06:06 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vector	set_projection_2_and_0(t_vector vector, t_mlx *mlx)
{
	double		x;
	double		y;
	double		z;
	double		sin_theta;
	double		cos_theta;

	if (mlx->projection == 0)
	{
		mlx->projection = 0;
		return (vector);
	}
	x = vector.x;
	y = vector.y;
	z = vector.z;
	sin_theta = sin(mlx->angle->x);
	cos_theta = cos(mlx->angle->y);
	vector.x = (x - y) * cos_theta;
	vector.y = (x + y) * sin_theta - z;
	return (vector);
}

t_vector	set_projection_1(t_vector vector, t_mlx *mlx)
{
	double		x;
	double		y;
	double		z;
	double		sin_theta;
	double		cos_theta;

	x = vector.x;
	y = vector.y;
	z = vector.z;
	sin_theta = sin(mlx->angle->x);
	cos_theta = cos(mlx->angle->y);
	vector.x = x * cos(mlx->angle->y) + sin_theta * z;
	vector.z = x * (-sin_theta) + cos_theta * z;
	vector.y = y * cos_theta + sin_theta * vector.z;
	return (vector);
}

void	finish_line_and_one_point(t_vector vec1, t_vector vec2, t_mlx *mlx)
{
	t_vector	end;

	end.x = round(vec2.x);
	end.y = round(vec2.y);
	if (!(mlx->map->width == 1 && mlx->map->height == 1))
		put_pixel_in_image(mlx->image,
			(int)round(vec1.x), (int)round(vec1.y), 0xFFFFFF);
	if (!((int)(vec1.x - end.x) && (int)(vec1.y - (int)end.y)))
		put_pixel_in_image(mlx->image,
			(int)round(end.x), (int)round(end.y), 0xFFFFFF);
	if (mlx->map->width == 1 && mlx->map->height == 1)
		put_pixel_in_image(mlx->image,
			(int)round(vec1.x), (int)round(vec1.y), 0xFFFFFF);
}

double	calculate_delta(t_vector vec1, t_vector vec2, int letter)
{
	double		delta_x;
	double		delta_y;
	double		max;

	delta_x = vec2.x - vec1.x;
	delta_y = vec2.y - vec1.y;
	max = ft_max_double(ft_abs_db(delta_x), ft_abs_db(delta_y));
	delta_x /= max;
	delta_y /= max;
	if (letter == 1)
		return (delta_x);
	if (letter == 2)
		return (delta_y);
	return (0);
}
