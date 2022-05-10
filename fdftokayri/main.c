/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 13:51:55 by jpuronah          #+#    #+#             */
/*   Updated: 2022/04/28 15:40:55 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_error(char *reason)
{
	ft_putendl(reason);
	exit(EXIT_FAILURE);
}

void	set_parameters(t_fdf *param)
{
	param->scale = 20;
	param->z_scale = 1;
	param->is_isometric = 1;
	param->angle = 0.523599;
	param->win_x = 2000;
	param->win_y = 1000;
	param->shift_x = param->win_x / 3;
	param->shift_y = param->win_y / 3;
	param->mlx_ptr = mlx_init();
	param->win_ptr =\
	mlx_new_window(param->mlx_ptr, param->win_x, param->win_y, "FDF");
}
/*
int		deal_key(int key, t_dot **matrix)
{
	if (is_key(key))
	{
		mlx_clear_window(PRM.mlx_ptr, PRM.win_ptr);
		do_key(key, matrix);
		print_menu(PRM);
		draw(matrix);
	}
	if (key == 6 || key == 7 || key == 0 || key == 1 || key == 3)
		new_window(key, matrix);
	if (key == '5')
	{
		mlx_destroy_window(PRM.mlx_ptr, PRM.win_ptr);
		free(matrix);
		exit(0);
	}
	return (0);
}
*/
int		deal_key(int key, t_fdf **matrix)
{
	if (key && key != XK_Escape)
	{
		mlx_clear_window(matrix[0][0].mlx_ptr, matrix[0][0].win_ptr);
		render(matrix);
	}
	if (key == XK_Escape)
	{
		mlx_destroy_window(matrix[0][0].mlx_ptr, matrix[0][0].win_ptr);
		free(matrix);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int		main(int argc, char **argv)
{
	t_fdf	**matrix;

	if (argc != 2)
		print_error("usage: ./fdf map.fdf");
	matrix = read_file(argv[1]);
	set_parameters(&matrix[0][0]);
	mlx_new_window(param->mlx_ptr, param->win_x, param->win_y, "FDF");
	mlx_new_window(matrix.mlx ->mlx_ptr, param->win_x, param->win_y, "FDF");
	render(matrix);
	mlx_key_hook(matrix[0][0].win_ptr, deal_key, matrix);
	mlx_loop(matrix[0][0].mlx_ptr);
	return (0);
}
