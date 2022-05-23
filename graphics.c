/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:27:13 by jpuronah          #+#    #+#             */
/*   Updated: 2022/05/23 17:12:39 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_and_exit(int key, t_mlx *mlx)
{
	int	i;

	i = 0;
	if (key == XK_Escape)
	{
		while (mlx->map->vectors[i] != NULL)
		{
			free(mlx->map->vectors[i]);
			i++;
		}
		free(mlx->map->vectors);
		free(mlx->map);
		free(mlx);
		exit(EXIT_SUCCESS);
	}
}

int		exit_with_esc(int key, t_mlx *mlx)
{
	(void)mlx;

	if (key == XK_Escape)
		free_and_exit(key, mlx);
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
	//free(map);
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

/*void	draw(int z, int x, int y)
{

}*/

void	render(t_mlx *mlx)
{
	int		x;
	int		y;

	y = 0;
	while (y < mlx->map->height)
	{
		x = 0;
		while (x < mlx->map->width)
		{
			mlx_string_put(mlx->mlxptr, mlx->winptr, 40 + x * 20, 40 + y * 20, WHITE, ft_itoa(mlx->map->vectors[x + (y * mlx->map->width)]->z));
			//draw(map->vectors[x + y]->z, x, y);
			x++;
		}
		y++;
	}
}

void	graphics(t_map *map, char *window_title)
{
	t_mlx	*mlx;

	mlx = init_mlx(window_title, map);
	if (mlx == NULL)
		printf_error ("Error; Cannot initialize mlx");
	if (mlx_key_hook(mlx->winptr, exit_with_esc, mlx) != 0)
		printf("moi");
	mlx_string_put(mlx->mlxptr, mlx->winptr, 20, 20, WHITE, "Press 'ESC' for EXIT");
	render(mlx);
	mlx_loop(mlx->mlxptr);
}
