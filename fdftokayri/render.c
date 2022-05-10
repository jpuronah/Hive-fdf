/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:10:41 by jpuronah          #+#    #+#             */
/*   Updated: 2022/04/28 15:29:42 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	zoom(t_fdf *a, t_fdf *b, t_fdf *param)
{
	a->x *= param->scale;
	a->y *= param->scale;
	b->x *= param->scale;
	b->y *= param->scale;
	a->z *= param->z_scale;
	b->z *= param->z_scale;
}

void	set_param(t_fdf *a, t_fdf *b, t_fdf *param)
{
	zoom(a, b, param);
	/*if (param->is_isometric)
	{
		isometric(a, param->angle);
		isometric(b, param->angle);
	}*/
	//printf("%d, %d\n", param->shift_x, param->shift_y);
	a->x += param->shift_x;
	a->y += param->shift_y;
	b->x += param->shift_x;
	b->y += param->shift_y;
}

double	fmodule(double i)
{
	return (i < 0) ? -i : i;
}

void	draw(t_fdf a, t_fdf b, t_fdf *param)
{
	double	step_x;
	double	step_y;
	double	max;
	int		color;

	set_param(&a, &b, param);
	step_x = b.x - a.x;
	step_y = b.y - a.y;
	max = step_x;
	if (fmodule(step_x) < fmodule(step_y))
		max = step_y;
	step_x /= max;
	step_y /= max;
	color = 0xFFFFFF;
	while ((a.x - b.x) != 0 || (a.y - b.y) != 0)
	{
		mlx_pixel_put(param->mlx_ptr, param->win_ptr, (int)a.x, (int)a.y, color);
		a.x += step_x;
		a.y += step_y;
		if (a.x > param->win_x || a.y > param->win_y || a.y < 0 || a.x < 0)
			break ;
	}
}

void	render(t_fdf **matrix)
{
	int		y;
	int		x;

	y = 0;
	while (matrix[y])
	{
		x = 0;
		while (1)
		{
			if (matrix[y + 1])
				draw(matrix[y][x], matrix[y + 1][x], &matrix[0][0]);
			if (!matrix[y][x].is_last)
				draw(matrix[y][x], matrix[y][x + 1], &matrix[0][0]);
			if (matrix[y][x].is_last)
				break ;
			x++;
		}
		y++;
	}
}