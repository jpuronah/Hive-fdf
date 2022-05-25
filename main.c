/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:43:13 by jpuronah          #+#    #+#             */
/*   Updated: 2022/05/25 16:40:07 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	printf_error(char *reason)
{
	ft_putendl(reason);
	exit(EXIT_FAILURE);
}

int	main(int ac, char **av)
{
	int			fd;
	int			param;

	fd = open(av[1], O_RDONLY);
	if (ac == 3 && fd > 0)
	{
		param = ft_atoi(av[2]);
		read_and_save_map(fd, param, av[1]);
	}
	else
		printf_error("error: wrong number of arguments");
	return (0);
}
