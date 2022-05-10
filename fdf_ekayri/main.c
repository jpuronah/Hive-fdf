/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 09:57:41 by jpuronah          #+#    #+#             */
/*   Updated: 2022/04/26 15:02:21 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//gcc -o fdf -I /usr/X11/include -g -L /usr/X11/lib -lX11 -lmlx -lXext *.c libft/libft.a


//		Kumpi error return (1) vai EXIT(1)

void	print_error(char *reason)
{
	ft_putendl(reason);
	exit(EXIT_FAILURE);
}
//		Kumpi error return (1) vai EXIT(1)
/*
int	print_error(char *reason)
{
	ft_putendl(reason);
	return (1);
} 
*/

int	main(int argc, char **argv)
{
	t_map	*map;
	t_mlx	*mlx;
	int		fd;

	if (argc < 2)
		print_error("Error: No input file");
		// return (print_error("Error: No input file"));
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		print_error("Error: Can't open file");
	if (!read_file_and_make_map(fd, &map))
		print_error("Error: Invalid file");
	mlx = initialize_mlx(argv[1]);
	if (mlx == NULL)
		print_error("Error; Cannot initialize mlx");
	mlx->map = map;
	render(mlx);
	mlx_key_hook(mlx->window, exit_with_esc, mlx);
	/*
	#define KeyPress		2
	#define KeyRelease		3
	#define ButtonPress		4
	#define ButtonRelease		5
	#define MotionNotify		6
	*/
	/*mlx_hook(mlx->mlxptr, 4, 0, hook_mousedown, mlx);
	mlx_hook(mlx->mlxptr, 5, 0, hook_mouseup, mlx);
	mlx_hook(mlx->mlxptr, 6, 0, hook_mousemove, mlx);*/
	mlx_loop(mlx->mlxptr);
	return (0);
}
