/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 23:31:04 by jpuronah          #+#    #+#             */
/*   Updated: 2022/05/19 23:34:26 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vector	**get_vectors(char *save)
{
	t_vector	**vectors;

	vectors = ft_memalloc(sizeof(t_vector));
	printf("vectors: %s\n", save);
	return (vectors);
}
