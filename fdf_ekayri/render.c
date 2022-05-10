/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 07:51:41 by jpuronah          #+#    #+#             */
/*   Updated: 2022/04/28 13:46:06 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

#define RED_PIXEL 0xFF0000

void	clear_image(t_image *image)
{
	ft_bzero(image->ptr, WIN_WIDTH * WIN_HEIGHT * image->bpp);
}

int	draw_line(t_mlx *mlx, t_vector vec1, t_vector vec2)
{
	double	deltaX;
	double	deltaY;
	double	deltaZ;
	double	pixelX;
	double	pixelY;
	int		pixels;
	int		color;

	color = vec1.color;
	color = 0xFFFFFF;

	deltaX = vec2.x - vec1.x;
	deltaY = vec2.y - vec1.y;
	deltaZ = vec2.z - vec1.z;
	pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY) + (deltaZ * deltaZ));

	deltaX /= pixels;
	deltaY /= pixels;
	deltaZ /= pixels;

	pixelX = vec1.x;
	pixelY = vec1.y;
	while (pixels)
	{
		mlx_pixel_put(mlx->mlxptr, mlx->window, pixelX, pixelY, color);
		pixelX += deltaX;
		pixelY += deltaY;
		--pixels;
	}
	return (0);
}

t_vector	project_vector(t_vector v, t_mlx *mlx)
{
	v.x -= (double)(mlx->map->width - 1) / 2.0f;
	v.y -= (double)(mlx->map->height - 1) / 2.0f;
	v.z -= (double)(mlx->map->depth_min + mlx->map->depth_max) / 2.0f;
	/*v = rotate(v, mlx->cam);
	v.x *= mlx->cam->scale;
	v.y *= mlx->cam->scale;
	v.x += mlx->cam->offsetx;
	v.y += mlx->cam->offsety;*/
	return (v);
}

t_vector	get_vector_for_render(t_map *map, int x, int y)
{
	printf("%d\n", y * map->width + x);
	return (*map->vectors[y * map->width + x]);
}

/*t_vector	*get_vector_for_render(t_map map, int x, int y, int z)
{
	t_vector	*vector;

	vector = ft_memalloc(sizeof(t_vector));
	if (vector == NULL)
		return (NULL);
	vector->x = (double)x;
	vector->y = (double)y;
	vector->z = (double)z;
	vector->color = 0xFFFFFF;
	return (vector);
}*/

void	render(t_mlx *mlx)
{
	int			x;
	int			y;
	t_vector	vector;
	t_map		*map;

	map = mlx->map;
	clear_image(mlx->image);
	x = 0;
	while (x < map->width)
	{
		y = 0;
		while (y < map->height)
		{
			vector = project_vector(get_vector_for_render(map, x, y), mlx);
			printf("x: %f, y: %f, z: %f, color: %d\n", vector.x, vector.y, vector.z, vector.color);
			if (x + 1 < map->width)
				draw_line(mlx, vector, project_vector(get_vector_for_render(map, x + 1, y), mlx));
			if (y + 1 < map->height)
				draw_line(mlx, vector, project_vector(get_vector_for_render(map, x, y + 1), mlx));
			/*v = project_vector(vector_at(map, x, y), mlx);
			if (x + 1 < map->width)
				line(mlx, v, project_vector(vector_at(map, x + 1, y), mlx));
			if (y + 1 < map->height)
				line(mlx, v, project_vector(vector_at(map, x, y + 1), mlx));*/
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(mlx->mlxptr, mlx->window, mlx->image->image, 0, 0);
}
