/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 20:30:19 by jeseo             #+#    #+#             */
/*   Updated: 2022/11/21 21:56:32 by jeseo            ###   ########.fr       */
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

void	pressed_wasd(int keycode, t_set *set)
{
	static int move_cnt;
	int		check;
	int 	move;

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
		if (set->map[set->p] == 'C')
			set->coll_cnt--;
		if (set->map[set->p] != 'E')
			set->map[set->p] = '0';
		else if (set->coll_cnt == 1)
		{
			set->flag |= CLEAR_FLAG;
			clear_game(set);
		}
		set->move_count = ft_itoa(++move_cnt);
		if (set->move_count == NULL)
			exit(EXIT_FAILURE);
	}
	if (check_flag(ENM_FLAG, set->flag) == 0)
	{
		if (set->map[set->e + move] != '1' && set->map[set->e + move] != 'C' && set->map[set->e + move] != 'E')
		{
			set->e += move;
			set->map[set->e - move] = '0';
			set->map[set->e] = '@';
		}
		if (set->e == set->p)
			clear_game(set);
	}
}

void	clear_game(t_set *set)
{
	if (check_flag(CLEAR_FLAG, set->flag) == -1)
		write(1, "GAME OVER\n", 10);
	else
		write(1, "GAME CLEAR\n", 11);
	exit(EXIT_SUCCESS);
}//무슨 차이??

void	pressed_esc(void)
{
	write(1, "GAME OVER\n", 11);
	exit(EXIT_SUCCESS);
}