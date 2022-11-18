/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:13:10 by jeseo             #+#    #+#             */
/*   Updated: 2022/11/18 21:03:23 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	print_binary(int n)
{
	if (n < 2)
		printf("%d", n % 2);
	else
	{
		print_binary(n / 2);
		print_binary(n % 2);
	}
}

int check_line_len(t_set *set, int i)
{
	if (set->map_height == 0)
		set->line_len = i;
	else if (set->line_len != i)
		return (-1);
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
		if ((i == 0) || (i == set->line_len - 1))
		{
			if (set->check_map[i] != '1')
				set->flag |= WALL_FLAG;
		}
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
			printf("map[%d]: %d\n", i, set->check_map[i]);
			return (ERROR);
		}
		i++;
	}
	return (check_line_len(set, i));
}

int	check_components(t_set *set)
{
	int	i;

	i = 0;
	while (set->map && set->map[i])
	{
		if (i < (set->line_len) || (set->map_height * (set->line_len - 1) < i && i < set->map_height * set->line_len))
		{
			printf("map[%d]: %c\n", i, set->map[i]);
			if (set->map[i] != '1')
			{
				write(2, "WALL ERROR\n", 11);
				return (ERROR);
			}
		}
		i++;
	}
	if (WALL_FLAG & set->flag || !(COLL_FLAG & set->flag) || \
		!(EXIT_FLAG & set->flag) || !(HERO_FLAG & set->flag))
	{
		print_binary(set->flag);
		write(2, "COMPONENTS ERROR\n", 17);
		return (ERROR);
	}
	if (set->line_len < 3 || set->map_height < 3)
	{
		write(2, "LINE TOO SHORT\n", 15);
		return (ERROR);
	}
	return (0);
}

void	find_route(char *map, int current, int *collectable, int width)
{
	static int	coll_flag;
	// int	i;

	// i = 0;
	//printf("===============================\n");
	//while (map[i])
	//{
	//	printf("%c", map[i]);
	//	if (i % width == width - 1)
	//		printf("\n");
	//	i++;
	//}
	if (map[current] == 'P')
	{
		printf("P: %d\n", current);
		printf("coll_flag: %d, collectable: %d\n", coll_flag, *collectable);
		coll_flag = *collectable + 1;
	}
	else if (map[current] == 'C' || map[current] == 'E')
		coll_flag--;
	if (coll_flag == 0) // escape까지 포함하기 때문에 -1.
	{
		*collectable = 0;
		return ;
	}
	else if (map[current] != '@' && map[current] != '1' && coll_flag != 0)
	{
		map[current] = '@';
		find_route(map, current + width, collectable, width);
		find_route(map, current + 1, collectable, width);
		find_route(map, current - width, collectable, width);
		find_route(map, current - 1, collectable, width);
		//map[current] = '0';
	}
}
