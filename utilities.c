/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:11:17 by jpuronah          #+#    #+#             */
/*   Updated: 2022/06/01 14:35:36 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_and_exit(int key, t_mlx *mlx)
{
	if (key == XK_Escape)
	{
		free(mlx->map->vectors);
		mlx->map->height = 0;
		mlx->map->width = 0;
		free(mlx->map);
		mlx->map = NULL;
		free(mlx);
		mlx = NULL;
		exit(EXIT_SUCCESS);
	}
}
