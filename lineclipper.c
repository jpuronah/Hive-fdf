/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lineclipper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 19:11:01 by jpuronah          #+#    #+#             */
/*   Updated: 2022/06/12 14:53:51 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		bitwise_vector_region(double x, double y)
{
	int vector_region;

	vector_region = 0;
	if (y > WIN_HEIGHT)
		vector_region |= 1;
	else if (y < 0)
		vector_region |= 2;
	if (x > WIN_WIDTH)
		vector_region |= 4;
	else if (x < 0)
		vector_region |= 8;
	/*if (y > WIN_HEIGHT)
		vector_region = 1;
	else if (y < 0)
		vector_region = 2;
	if (x > WIN_WIDTH)
		vector_region = 4;
	else if (x < 0)
		vector_region = 8;*/
	return (vector_region);
}

t_vector	find_line_segment(t_vector tmp_vec, t_vector *p1, t_vector *p2, int routine)
{
	//if (routine == 1)  // TÄMÄ EI KÄY MUTTA MIKSI VITUSSA?
	if (routine & 1)
	{
		tmp_vec.x = p1->x + (p2->x - p1->x) * (WIN_HEIGHT - p1->y) / (p2->y - p1->y);
		tmp_vec.y = WIN_HEIGHT;
	}
	else if (routine & 2)
	{
		tmp_vec.x = p1->x + (p2->x - p1->x) * -p1->y / (p2->y - p1->y);
		tmp_vec.y = 0;
	}
	else if (routine & 4)
	{
		tmp_vec.x = WIN_WIDTH;
		tmp_vec.y = p1->y + (p2->y - p1->y) * (WIN_WIDTH - p1->x) / (p2->x - p1->x);
	}
	else if (routine & 8)
	{
		tmp_vec.x = 0;
		tmp_vec.y = p1->y + (p2->y - p1->y) * -p1->x / (p2->x - p1->x);
	}
	return (tmp_vec);
}

int		cohen_sutherland_lineclip(t_vector *vector1, t_vector *vector2)
{
	t_vector	tmp_vec;
	int			region_vec1;
	int			region_vec2;
	int			draw_routine;

	/*region_vec1 = 0;
	region_vec2 = 0;
	if (vector1->y > WIN_HEIGHT)
		region_vec1 |= 1;
	else if (vector1->y < 0)
		region_vec1 |= 2;
	if (vector1->x > WIN_WIDTH)
		region_vec1 |= 4;
	else if (vector1->x < 0)
		region_vec1 |= 8;
	if (vector2->y > WIN_HEIGHT)
		region_vec2 |= 1;
	else if (vector2->y < 0)
		region_vec2 |= 2;
	if (vector2->x > WIN_WIDTH)
		region_vec2 |= 4;
	else if (vector2->x < 0)
		region_vec2 |= 8;*/
	region_vec1 = bitwise_vector_region(vector1->x, vector1->y);
	region_vec2 = bitwise_vector_region(vector2->x, vector2->y);
	//while (!(!(region_vec1 | region_vec2) || (region_vec1 & region_vec2)))
	while ((region_vec1 | region_vec2) != 0 && (region_vec1 & region_vec2) == 0)
	{
		//draw_routine = region_vec1 ? region_vec1 : region_vec2;
		if (region_vec1 > 0)
			draw_routine = region_vec1;
		else
			draw_routine = region_vec2;
		tmp_vec = find_line_segment(tmp_vec, vector1, vector2, draw_routine);
		if (draw_routine == region_vec1)
		{
			vector1->x = tmp_vec.x;
			vector1->y = tmp_vec.y;
			region_vec1 = bitwise_vector_region(vector1->x, vector1->y);
		}
		else
		{
			vector2->x = tmp_vec.x;
			vector2->y = tmp_vec.y;
			region_vec2 = bitwise_vector_region(vector2->x, vector2->y);
		}
	}
	//return (!(region_vec1 | region_vec2));
	if (region_vec1 == 0 && region_vec2 == 0)
		return (1);
	else//if (region_vec1 != 0 && region_vec2 != 0)
		return (0);
}
