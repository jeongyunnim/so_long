/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:13:10 by jeseo             #+#    #+#             */
/*   Updated: 2022/11/12 16:06:37 by jeseo            ###   ########.fr       */
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

int	check_line(char *map, t_flags *flags)
{
	static char	*save;
	int			i;

	i = 0;
	if (!(END_FLAG & (*flags).flag)) // 끝나지 않았을 때. 체크하고 할당.
	{
		while (map[i] != '\0' && map[i] != '\n')
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
				printf("WRONG COMPONENT:%c\n", map[i]);
				write(2, "FOUND WRONG COMPONENT\n", 22);
				return (ERROR);
			}
			i++;
		}
		save = strdup(map);
		if (save == NULL)
			return (ERROR);
	}
	printf("map_H: %d\n", (*flags).map_height);
	if (((*flags).map_height == 0) || ((END_FLAG & (*flags).flag)))
	{
		i = 0;
		while (save != NULL && save[i] != '\0' && save[i] != '\n')
		{
			if (save[i] != '1')
				(*flags).flag |= WALL_FLAG;
			i++;
		}
		(*flags).line_len = i;
		if ((END_FLAG & (*flags).flag))
		{
			free(save);
			save = NULL;
		}
	}
	else if (!((*flags).map_height == 0) && (*flags).line_len != i && (*flags).map_height == 1)
	{
		printf("line: %d\ni: %d\n",(*flags).line_len, i);
		write(2, "LINE LENGTH ERROR\n", 18);
		return (ERROR);
	}
	return (1);
}

int	check_components(int flag, int len)
{
	if (WALL_FLAG & flag || !(COLL_FLAG & flag) || \
		!(EXIT_FLAG & flag) || !(HERO_FLAG & flag))
	{
		print_binary(flag);
		write(2, "COMPONENTS ERROR\n", 17);
		return (ERROR);
	}
	if (len < 3)
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
	printf("===============================\n");
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
		printf("moved down v\n");
		find_route(map, current + width, collectable, width);
		printf("moved right >\n");
		find_route(map, current + 1, collectable, width);
		printf("moved up ^\n");
		find_route(map, current - width, collectable, width);
		printf("moved left <\n");
		find_route(map, current - 1, collectable, width);
		//map[current] = '0';
	}
}
