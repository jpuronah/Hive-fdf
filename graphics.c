/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:27:13 by jpuronah          #+#    #+#             */
/*   Updated: 2022/05/20 17:41:17 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		exit_with_esc(int key, t_mlx *mlx)
{
	(void)mlx;
	//printf("%d\n", key);
	if (key == XK_Escape)
		exit(EXIT_SUCCESS);
	return (0);
}

t_mlx	*init_mlx(char *win_title, t_map *map)
{
	t_mlx	*mlx;

	mlx = ft_memalloc(sizeof(t_mlx));
	if (!mlx)
		return (NULL);
	mlx->mlxptr = mlx_init();
	mlx->winptr = mlx_new_window(mlx->mlxptr, WIN_WIDTH, WIN_HEIGHT, win_title);
	mlx->map = map;
	//mlx->image = new_image(mlx);
	//mlx->mouse = ft_memalloc(sizeof(t_mouse));
	//mlx->cam = ft_memalloc(sizeof(t_cam));
	//if (mlx->mlxptr == NULL || mlx->window == NULL || mlx->cam == NULL ||
	//		mlx->image == NULL || mlx->mouse == NULL)
	//	return (mlxdel(mlx));
	/*mlx->cam->x = 0.5;
	mlx->cam->y = 0.5;
	mlx->cam->scale = 32;
	mlx->cam->offsetx = WIN_WIDTH / 2;
	mlx->cam->offsety = WIN_HEIGHT / 2;*/
	return (mlx);
}

void	graphics(t_map *map, char *window_title)
{
	t_mlx	*mlx;

	mlx = init_mlx(window_title, map);
	if (mlx == NULL)
		printf_error ("Error; Cannot initialize mlx");
	
	mlx_key_hook(mlx->winptr, exit_with_esc, mlx);
	mlx_loop(mlx->mlxptr);



	/*printf("%d, %d\n", mlx->map->width, mlx->map->height);
	int i = 0;
	while (i < (mlx->map->height * mlx->map->width))
	{
		printf("z (%d, %d): %d\n", mlx->map->vectors[i]->x, mlx->map->vectors[i]->y, mlx->map->vectors[i]->z);
		i++;
	}*/
}
