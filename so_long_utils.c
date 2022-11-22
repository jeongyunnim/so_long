/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:21:52 by jeseo             #+#    #+#             */
/*   Updated: 2022/11/22 17:50:08 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

int	deley_n(int n)
{
	static unsigned int	t;

	t++;
	return ((t / 12) % n);
}

void	print_error(t_set set)
{
	write(1, "ERROR\n", 6);
	if (set.coll_cnt == 0)
		write(1, "ROUTE ERROR\n", 13);
	if (set.coll_cnt == -1)
		write(1, "COMPONENT ERROR\n", 16);
	if (WALL_FLAG & set.flag)
		write(1, "WALL ERROR\n", 11);
	if (!(COLL_FLAG & set.flag))
		write(1, "HAVE NO COLLECTABLE THING\n", 26);
	if (!(EXIT_FLAG & set.flag))
		write(1, "HAVE NO EXIT\n", 13);
	if (!(HERO_FLAG & set.flag))
		write(1, "HAVE NO PLAYER\n", 15);
	if (RECT_FLAG & set.flag)
		write(1, "HAVE NO PLAYER\n", 15);
	write(1, "MAP CAN NOT BE DRAWN\n", 21);
	exit(EXIT_FAILURE);
}

void	sprint_img(t_set *set, void *img[], int i)
{
	int	x;
	int	y;

	x = (i % set->line_len) * 64;
	y = (i / set->line_len) * 64;
	if (i == set-> p)
		mlx_put_image_to_window(set->mlx, set->win, img[deley_n(5)], x, y);
	else if (set->map[i] == '@')
		mlx_put_image_to_window(set->mlx, set->win, img[deley_n(2)], x, y);
}

void	make_enm(t_set *set)
{
	int		i;
	char	locate;
	char	component;

	i = 0;
	while (set->check_map[i] != '\0')
	{
		locate = set->check_map[i];
		component = set->map[i];
		if (locate == '@' && component != 'C'\
		&& component != 'E' && i != set->p)
		{
			set->flag |= ENM_FLAG;
			set->e = i;
			set->map[i] = '@';
			return ;
		}
		i++;
	}
	free_string(&(set->check_map));
}

void	free_string(char **target)
{
	if (*target != NULL)
		free(*target);
	*target = NULL;
}
