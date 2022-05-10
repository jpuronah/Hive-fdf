/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_save_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuronah <jpuronah@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:14:40 by jpuronah          #+#    #+#             */
/*   Updated: 2022/04/28 13:32:37 by jpuronah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	cleanup(t_list **list, t_map **map)
{
	t_list	*next;

	while (*list)
	{
		next = (*list)->next;
		ft_memdel(&(*list)->content);
		ft_memdel((void **)list);
		*list = next;
	}
	if (map && *map)
	{
		ft_memdel((void **)&(*map)->vectors);
		ft_memdel((void **)map);
	}
	return (0);
}

int	ft_splitdel(char ***split)
{
	char	**str;
	int		i;

	i = 0;
	str = *split;
	while (*str)
	{
		ft_strdel(str);
		i++;
		str = &(*split)[i];
	}
	ft_memdel((void **)split);
	return (0);
}

static int	save_fd_to_list(int fd, t_list **list)
{
	t_list	*temp;
	char	*line;
	int		ret;
	int		width;

	int row; //turha
	int	i;   //turha
	row = 0;

	width = -1;
	ret = get_next_line(fd, &line);
	while (ret)
	{
		if (width == -1)
			width = (int)ft_countwords(line, ' ');
		temp = ft_lstnew(line, ft_strlen(line) + 1);
		if (temp == NULL)
			return (cleanup(list, NULL));
		ft_lstadd(list, temp);
		if (width != (int)ft_countwords(line, ' '))
			return (cleanup(list, NULL));
		ft_strdel(&line);
		ret = get_next_line(fd, &line);
		row++;
	}
	if (width == -1 || ret == -1)
		return (cleanup(list, NULL));
	ft_lstrev(list);

	i = -1;
	while (i++ < row - 1)
		printf("row %d: %s\n", i + 1, (char *)(ft_lstat(*list, i))->content);
	return (1);
}


static int fill_map(t_map **map, t_list *list)
{
	char	**split_list;
	int		x;
	int		y;

	y = 0;
	while (y < (*map)->height)
	{
		x = 0;
		split_list = ft_strsplit(list->content, ' ');
		if (split_list == NULL)
			return (cleanup(&list, map));
		while (x < (*map)->width)
		{
			(*map)->vectors[y * (*map)->width + x] = get_vector_for_map(x, y, split_list[x]);
			x++;
		}
		ft_splitdel(&split_list);
		list = list->next;
		y++;
	}
	map_depth(*map);
	fill_colors(*map);
	cleanup(&list, NULL);
	return (0);
}

int	read_file_and_make_map(int fd, t_map **map)
{
	t_list	*list;

	list = NULL;
	if (!save_fd_to_list(fd, &list))
		return (0);
	*map = malloc_map(ft_countwords(list->content, ' '), ft_lstcount(list));
	if (*map == NULL)
		return (cleanup(&list, map));
	fill_map(map, list);
	return (1);
}
