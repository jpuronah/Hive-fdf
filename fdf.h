/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:43:12 by jpuronah          #+#    #+#             */
/*   Updated: 2022/05/19 23:36:18 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>

typedef struct s_vector
{
	int			x;
	int			y;
	int			z;
}				t_vector;

typedef struct s_map
{
	int			width;
	int			height;
	t_vector	**vectors;
}				t_map;

typedef struct s_mlx
{
	void		*mlxptr;
	void		*winptr;
	t_map		*map;
}				t_mlx;

void		printf_error(char *reason);

t_map		*init_map(void);
t_map		*read_and_save_map(int fd);
void		get_map_width(char *line, t_map *map);
void		get_map_parameters(char *line, t_map *map);

t_vector	**get_vectors(char *save);

#endif
