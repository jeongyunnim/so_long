/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:13:10 by jeseo             #+#    #+#             */
/*   Updated: 2022/11/16 22:49:58 by jeseo            ###   ########.fr       */
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

int check_line_len(t_flags *flags, int i)
{
	if ((*flags).map_height == 0)
		(*flags).line_len = i;
	else if ((*flags).line_len != i)
		return (-1);
	return (0);
}

int	check_line(char *map, t_flags *flags)
{
	int			i;

	i = 0;
	if (map == NULL)
		return (0);
	while (map[i] != '\n' && map[i] != '\0')
	{
		if ((i == 0) || (i == (*flags).line_len - 1))
		{
			if (map[i] != '1')
				(*flags).flag |= WALL_FLAG;
		}
		if (map[i] == 'C')
		{
			(*flags).flag |= COLL_FLAG;
			(*flags).coll_cnt++;
		}
		else if (map[i] == 'E' && !(EXIT_FLAG & (*flags).flag))
			(*flags).flag |= EXIT_FLAG;
		else if (map[i] == 'P' && !(HERO_FLAG & (*flags).flag))
		{
			(*flags).p = i + (*flags).map_height * (*flags).line_len;
			(*flags).flag |= HERO_FLAG;
		}
		else if (map[i] != '1' && map[i] != '0')
		{
			printf("map[%d]: %d\n", i, map[i]);
			return (ERROR);
		}
		i++;
	}
	return (check_line_len(flags, i));
}

int	check_components(char *map, t_flags flag)
{
	int	i;

	i = 0;
	while (map && map[i])
	{
		if (i < (flag.line_len) || (flag.map_height * (flag.line_len - 1) < i && i < flag.map_height * flag.line_len))
		{
			printf("map[%d]: %c\n", i, map[i]);
			if (map[i] != '1')
			{
				write(2, "WALL ERROR\n", 11);
				return (ERROR);
			}
		}
		i++;
	}
	if (WALL_FLAG & flag.flag || !(COLL_FLAG & flag.flag) || \
		!(EXIT_FLAG & flag.flag) || !(HERO_FLAG & flag.flag))
	{
		print_binary(flag.flag);
		write(2, "COMPONENTS ERROR\n", 17);
		return (ERROR);
	}
	if (flag.line_len < 3 || flag.map_height < 3)
	{
		write(2, "LINE TOO SHORT\n", 15);
		return (ERROR);
	}
	return (0);
}

void	find_route(char *map, int current, int *collectable, int width)
{
	static int	coll_flag;
	char		**map_temp;

	map_temp = &map;
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
	if (*map_temp[current] == 'P')
	{
		printf("P: %d\n", current);
		printf("coll_flag: %d, collectable: %d\n", coll_flag, *collectable);
		coll_flag = *collectable + 1;
	}
	else if (*map_temp[current] == 'C' || *map_temp[current] == 'E')
		coll_flag--;
	if (coll_flag == 0) // escape까지 포함하기 때문에 -1.
	{
		*collectable = 0;
		return ;
	}
	else if (*map_temp[current] != '@' && *map_temp[current] != '1' && coll_flag != 0)
	{
		*map_temp[current] = '@';
		find_route(*map_temp, current + width, collectable, width);
		find_route(*map_temp, current + 1, collectable, width);
		find_route(*map_temp, current - width, collectable, width);
		find_route(*map_temp, current - 1, collectable, width);
		//map[current] = '0';
	}
}
