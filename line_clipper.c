/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_clipper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 19:11:01 by jpuronah          #+#    #+#             */
/*   Updated: 2022/06/12 20:42:43 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	bitwise_vector_region(double x, double y)
{
	int	vector_region;

	vector_region = 0;
	if (y > WIN_HEIGHT)
		vector_region |= 1;
	else if (y < 0)
		vector_region |= 2;
	if (x > WIN_WIDTH)
		vector_region |= 4;
	else if (x < 0)
		vector_region |= 8;
	return (vector_region);
}

static t_vector	line_segment(t_vector tmp_vec,
	t_vector *p1, t_vector *p2, int draw_routine)
{
	t_vector	delta;

	delta.x = p2->x - p1->x;
	delta.y = p2->y - p1->y;
	if (draw_routine & 1)
	{
		tmp_vec.x = p1->x + delta.x * (WIN_HEIGHT - p1->y) / delta.y;
		tmp_vec.y = WIN_HEIGHT;
	}
	else if (draw_routine & 2)
	{
		tmp_vec.x = p1->x + delta.x * (-p1->y) / delta.y;
		tmp_vec.y = 0;
	}
	else if (draw_routine & 4)
	{
		tmp_vec.x = WIN_WIDTH;
		tmp_vec.y = p1->y + delta.y * (WIN_WIDTH - p1->x) / delta.x;
	}
	else if (draw_routine & 8)
	{
		tmp_vec.x = 0;
		tmp_vec.y = p1->y + delta.y * (-p1->x) / delta.x;
	}
	return (tmp_vec);
}

int	cohen_sutherland_lineclip(t_vector *vector1, t_vector *vector2)
{
	t_line_clip	ln;

	ln.region1 = bitwise_vector_region(vector1->x, vector1->y);
	ln.region2 = bitwise_vector_region(vector2->x, vector2->y);
	while ((ln.region1 | ln.region2) != 0 && (ln.region1 & ln.region2) == 0)
	{
		if (ln.region1 > 0)
			ln.drawroutine = ln.region1;
		else
			ln.drawroutine = ln.region2;
		ln.tmp_vec = line_segment(ln.tmp_vec, vector1, vector2, ln.drawroutine);
		if (ln.drawroutine == ln.region1)
		{
			vector1->x = ln.tmp_vec.x;
			vector1->y = ln.tmp_vec.y;
			ln.region1 = bitwise_vector_region(vector1->x, vector1->y);
		}
		else
		{
			vector2->x = ln.tmp_vec.x;
			vector2->y = ln.tmp_vec.y;
			ln.region2 = bitwise_vector_region(vector2->x, vector2->y);
		}
	}
	return (!(ln.region1 | ln.region2));
}
