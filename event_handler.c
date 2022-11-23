/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:13:41 by jeseo             #+#    #+#             */
/*   Updated: 2022/11/23 13:56:32 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

int	destroy_handler(t_set *set)
{
	mlx_destroy_window(set->mlx, set->win);
	exit(EXIT_SUCCESS);
	return (0);
}

int	key_handler(int key_code, t_set *set)
{
	if (key_code == S || key_code == D || key_code == W || key_code == A)
	{
		pressed_wasd(key_code, set);
	}
	if (key_code == ESC)
	{
		pressed_esc();
	}
	return (0);
}

void	pressed_wasd(int keycode, t_set *set)
{
	static int	move_cnt;
	int			move;
	int			check;

	move = 0;
	check = set->p;
	if (keycode == W)
		move = set->line_len * -1;
	else if (keycode == A)
		move = -1;
	else if (keycode == S)
		move = set->line_len;
	else if (keycode == D)
		move = 1;
	if (set->map[check + move] != '1')
	{
		set->p += move;
		movement(set, set->map[set->p], move, 'P');
		print_move_cnt(set, ++move_cnt);
	}
	if (check_flag(ENM_FLAG, set->flag) == 0)
		movement(set, set->map[set->e + move], move, 'E');
}

void	pressed_esc(void)
{
	write(1, "GAME OVER\n", 11);
	exit(EXIT_SUCCESS);
}

void	movement(t_set *set, char current, int move, char who)
{
	if (who == 'P')
	{
		if (current == 'C')
			set->coll_cnt--;
		if (current != 'E')
			set->map[set->p] = '0';
		else if (set->coll_cnt == 1)
		{
			set->flag |= CLEAR_FLAG;
			clear_game(set);
		}
	}
	else
	{
		if (current != '1' && current != 'C' && current != 'E')
		{
			set->e += move;
			set->map[set->e - move] = '0';
			set->map[set->e] = '@';
		}
		if (set->e == set->p)
			clear_game(set);
	}
}
