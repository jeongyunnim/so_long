/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:21:52 by jeseo             #+#    #+#             */
/*   Updated: 2022/11/23 14:06:08 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

void	print_error(t_set set)
{
	write(1, "ERROR\n", 6);
	if (set.coll_cnt != 0)
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
		write(1, "MAP MUST BE RECTANGLE\n", 22);
	write(1, "MAP CAN NOT BE DRAWN\n", 21);
	exit(EXIT_FAILURE);
}

void	free_string(char **target)
{
	if (*target != NULL)
		free(*target);
	*target = NULL;
}

void	print_move_cnt(t_set *set, int move_cnt)
{
	char		*move_str;

	move_str = ft_itoa(move_cnt);
	if (move_str == NULL)
		print_error(*set);
	write(1, "move: ", 6);
	write(1, move_str, ft_strlen(move_str));
	write(1, "\n", 1);
	free_string(&move_str);
}

size_t	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}
