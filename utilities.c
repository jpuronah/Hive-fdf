/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:11:17 by jpuronah          #+#    #+#             */
/*   Updated: 2022/06/01 12:28:59 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


void	free_and_exit(int key, t_mlx *mlx)
{
	if (key == XK_Escape)
	{
		/*while (mlx->map->vectors[i])
		{
			free(mlx->map->vectors[i]);
			mlx->map->vectors[i]->x = 0;
			mlx->map->vectors[i]->y = 0;
			mlx->map->vectors[i]->z = 0;
			i++;
		}*/
		free(mlx->map->vectors);
		mlx->map->height = 0;
		mlx->map->width = 0;
		//free(mlx->mlxptr);
		//free(mlx->winptr);
		free(mlx->map);
		mlx->map = NULL;
		free(mlx);
		mlx = NULL;
		exit(EXIT_SUCCESS);
	}
}
