/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:12:53 by jpuronah          #+#    #+#             */
/*   Updated: 2022/06/03 13:09:57 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_pixel_in_image(t_image *image, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || x >= WIN_WIDTH + 1 || y < 0 || y >= WIN_HEIGHT + 1)
		return ;
	pixel = image->ptr + (y * image->line_bytes + x * (image->bpp));
	*(int *)pixel = color;
}

void	clear_image(t_image *image)
{
	ft_bzero(image->ptr, (size_t)(WIN_WIDTH * WIN_HEIGHT * image->bpp));
}

t_image	*delete_image(t_mlx *mlx, t_image *img)
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

	img = ft_memalloc(sizeof(t_image));
	if (img == NULL)
		return (NULL);
	img->image = mlx_new_image(mlx->mlxptr, WIN_WIDTH, WIN_HEIGHT);
	if (img->image == NULL)
		return (delete_image(mlx, img));
	img->ptr = mlx_get_data_addr(img->image, &img->bpp, &img->line_bytes,
			&img->endian);
	img->bpp /= 8;
	return (img);
}
