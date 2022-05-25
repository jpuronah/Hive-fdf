/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:12:53 by jpuronah          #+#    #+#             */
/*   Updated: 2022/05/25 16:33:08 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


void	image_set_pixel(t_image *image, int x, int y, int color)
{
	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
	{
		return ;
	}
	*(image->ptr + ((x + y * WIN_WIDTH) * image->bpp)) = color;
}

void	clear_image(t_image *image)
{
	ft_bzero(image->ptr, WIN_WIDTH * WIN_HEIGHT * image->bpp);
}

t_image	*del_image(t_mlx *mlx, t_image *img)
{
	if (img != NULL)
	{
		if (img->image != NULL)
			mlx_destroy_image(mlx->mlxptr, img->image);
		ft_memdel((void **)&img);
	}
	return (NULL);
}

t_image	*new_image(t_mlx *mlx)
{
	t_image		*img;

	if ((img = ft_memalloc(sizeof(t_image))) == NULL)
		return (NULL);
	if ((img->image = mlx_new_image(mlx->mlxptr, WIN_WIDTH, WIN_HEIGHT)) == NULL)
		return (del_image(mlx, img));
	img->ptr = mlx_get_data_addr(img->image, &img->bpp, &img->line_bytes,
			&img->endian);
	img->bpp /= 8;
	return (img);
}
