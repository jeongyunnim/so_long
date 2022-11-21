/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:13:10 by jeseo             #+#    #+#             */
/*   Updated: 2022/11/21 22:28:03 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int check_line_len(t_set *set, int i)
{
	int	len;
	int temp;

	len = set->line_len;
	temp = i;
	printf("map_height: %d\n%s\n%d,%d", set->map_height, set->check_map, len, temp);
	if (set->map_height == 0)
	{
		printf("초기화 할 게\n");
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

	i = 0;
	if (set->check_map == NULL)
		return (0);
	while (set->check_map[i] != '\n' && set->check_map[i] != '\0')
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
			return (ERROR);
		i++;
	}
	return (check_line_len(set, i));
}

int	check_components(t_set *set)
{
	int	i;
	int height;
	int width;

	i = 0;
	height = set->map_height;
	width = set->line_len;
	while (set->map && set->map[i])
	{
		if (i % width == 0|| i % width == width - 1 || \
		i < width || ((height - 1) * width <= i && i < height * width))
		{
			if (set->map[i] != '1')
				set->flag |= WALL_FLAG;
		}
		i++;
	}
	if (WALL_FLAG & set->flag || !(COLL_FLAG & set->flag) || \
		!(EXIT_FLAG & set->flag) || !(HERO_FLAG & set->flag) || (RECT_FLAG & set->flag))
	{
		printf("%d", set->flag);
		print_error(set->flag);
		return(ERROR);
	}
	//if (set->line_len < 3 || set->map_height < 3)
	//	return (ERROR);
	return (0);
}

void	print_error(char flag)
{
	write(1, "ERROR\n", 6);
	if (WALL_FLAG & flag)
		write(1, "WALL ERROR\n", 11);
	if (!(COLL_FLAG & flag))
		write(1, "HAVE NO COLLECTABLE THING\n", 26);
	if (!(EXIT_FLAG & flag))
		write(1, "HAVE NO EXIT\n", 13);
	if (!(HERO_FLAG & flag))
		write(1, "HAVE NO PLAYER\n", 15);
	if (RECT_FLAG &flag)
		write(1, "HAVE NO PLAYER\n", 15);
	write(1, "MAP CAN NOT BE DRAWN\n", 21);
}

void	find_route(char *map, int current, int *collectable, int width)
{
	static int	coll_flag;
	//int	i;

	// i = 0;
	//printf("===============================\n");
	//while (map[i])
	//{
	//	printf("%c", map[i]);
	//	if (i % width == width - 1)
	//		printf("\n");
	//	i++;
	//}
	
	if (map[current] == 'C' || map[current] == 'E')
		coll_flag++;
	if (coll_flag == *collectable + 1) // escape까지 포함하기 때문에 -1.
	{
		*collectable = 0;
		return ;
	}
	else if (map[current] != '@' && map[current] != '1' && coll_flag != *collectable + 1)
	{
		map[current] = '@';
		find_route(map, current + width, collectable, width);
		find_route(map, current + 1, collectable, width);
		find_route(map, current - width, collectable, width);
		find_route(map, current - 1, collectable, width);
		//map[current] = '0';
	}
}
