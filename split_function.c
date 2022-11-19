/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 20:30:19 by jeseo             #+#    #+#             */
/*   Updated: 2022/11/19 15:35:46 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_flag(char flag, char target)
{
	if ((flag & target) == 0)
	{
		return (-1);
	}
	else
		return (0);
}

void	free_string(char **target)
{
	if (*target != NULL)
		free(*target);
	*target = NULL;
}

void	pressed_s(t_set *set)
{
	int	check;

	check = set->p + set->line_len;
	if (set->map[check] != '1')
	{
		if (set->map[check] == 'C')
		{
			set->coll_cnt--;
		}
		set->map[set->p] = '0';
		set->p += set->line_len;
	}
	//mlx_clear_window(set->mlx, set->win);
	//draw_map(*set);
}

void	pressed_d(t_set *set)
{
	int	check;

	check = set->p + 1;
	if (set->map[check] != '1')
	{
		if (set->map[check] == 'C')
		{
			set->coll_cnt--;
		}
		set->map[set->p] = '0';
		set->p += 1;
	}
	//mlx_clear_window(set->mlx, set->win);
	//draw_map(*set);
}

void	pressed_w(t_set *set)
{	
	int	check;

	check = set->p - set->line_len;
	if (set->map[check] != '1')
	{
		if (set->map[check] == 'C')
		{
			set->coll_cnt--;
		}
		set->map[set->p] = '0';
		set->p -= set->line_len;
	}
	//mlx_clear_window(set->mlx, set->win);
	//draw_map(*set);
}

void	pressed_a(t_set *set)
{
	int	check;

	check = set->p - 1;
	if (set->map[check] != '1')
	{
		if (set->map[check] == 'C')
		{
			set->coll_cnt--;
		}
		set->map[set->p] = '0';
		set->p -= 1;
	}
	//mlx_clear_window(set->mlx, set->win);
	//draw_map(*set);
}

void	pressed_esc(void)
{
	exit(EXIT_SUCCESS);
}