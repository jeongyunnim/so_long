/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 19:09:59 by jeseo             #+#    #+#             */
/*   Updated: 2022/11/22 17:04:13 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_map(int fd, t_set *set)
{
	while (check_flag(END_FLAG, set->flag) == -1)
	{
		set->check_map = get_next_line(fd);
		if (set->check_map == NULL)
			set->flag |= END_FLAG;
		else if (check_line(set) != ERROR)
		{
			set->map = ft_strnjoin(&set->map, set->check_map, set->line_len);
			if (set->map == NULL)
				return (ERROR);
			set->map_height++;
		}
		else
			return (ERROR);
		free_string(&set->check_map);
	}
	if (check_components(set) == ERROR || check_valid(set) == ERROR)
		return (ERROR);
	write(1, "YOU CAN SOLVE! TRY! TRY!\n", 25);
	close(fd);
	return (0);
}

int	check_valid(t_set *set)
{
	int		count_temp;

	count_temp = 0;
	count_temp = set->coll_cnt + 1;
	set->check_map = ft_strdup(set->map);
	if (set->check_map == NULL)
		return (ERROR);
	find_route(set->check_map, set->p, &set->coll_cnt, set->line_len);
	if (set->coll_cnt != 0)
		return (ERROR);
	set->coll_cnt = count_temp;
	return (0);
}

int	check_extension(char *target)
{
	int	i;

	i = 0;
	while (target != NULL && target[i] != '\0')
	{
		i++;
	}
	if (target[i - 4] != '.' || target[i - 3] != 'b' || \
	target[i - 2] != 'e' || target[i - 1] != 'r')
		return (ERROR);
	return (0);
}
