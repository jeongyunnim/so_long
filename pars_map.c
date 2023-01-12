/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:13:10 by jeseo             #+#    #+#             */
/*   Updated: 2023/01/12 19:39:11 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

int	check_line_len(t_set *set, int i)
{
	int	len;
	int	temp;

	len = set->line_len;
	temp = i;
	if (set->map_height == 0)
	{
		set->line_len = i;
	}
	else if (set->line_len != i)
	{
		set->flag |= RECT_FLAG;
		return (ERROR);
	}
	return (0);
}

int	check_line(t_set *set)
{
	int			i;

	i = -1;
	while (set->check_map[++i] != '\n')
	{
		if (set->check_map[i] == 'C')
		{
			set->flag |= COLL_FLAG;
			set->coll_cnt++;
		}
		else if (set->check_map[i] == 'E' && !(EXIT_FLAG & set->flag))
			set->flag |= EXIT_FLAG;
		else if (set->check_map[i] == 'P' && !(HERO_FLAG & set->flag))
		{
			set->p = i + (set->map_height * set->line_len);
			set->flag |= HERO_FLAG;
		}
		else if (set->check_map[i] != '1' && set->check_map[i] != '0')
		{
			set->coll_cnt = -1;
			return (ERROR);
		}
	}
	return (check_line_len(set, i));
}

int	check_components(t_set *set)
{
	int	i;
	int	height;
	int	width;

	i = 0;
	height = set->map_height;
	width = set->line_len;
	while (set->map && set->map[i])
	{
		if (i % width == 0 || i % width == width - 1 || \
		i < width || ((height - 1) * width <= i && i < height * width))
		{
			if (set->map[i] != '1')
				set->flag |= WALL_FLAG;
		}
		i++;
	}
	if (WALL_FLAG & set->flag || !(COLL_FLAG & set->flag) || \
		!(EXIT_FLAG & set->flag) || !(HERO_FLAG & set->flag) || \
		(RECT_FLAG & set->flag))
	{
		return (ERROR);
	}
	return (0);
}

void	find_route(char *map, int current, int *collectable, int width)
{
	static int	coll_flag;
	int			i;

	i = 0;
	if (map[current] == 'C' || map[current] == 'E')
		coll_flag++;
	if (coll_flag >= *collectable + 1)
	{
		if (coll_flag > *collectable)
			printf("넘어갔음... static: %d, struct: %d\n", coll_flag, *collectable);
		*collectable = 0;
		return ;
	}
	else if (map[current] != '@' && \
	map[current] != '1' && coll_flag != *collectable + 1)
	{
		map[current] = '@';
		find_route(map, current + width, collectable, width);
		find_route(map, current + 1, collectable, width);
		find_route(map, current - width, collectable, width);
		find_route(map, current - 1, collectable, width);
		map[current] = '0';
	}
}
