/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:13:37 by jeseo             #+#    #+#             */
/*   Updated: 2022/11/23 13:28:08 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

int	draw_map(t_set *set)
{
	int	i;
	int	x;
	int	y;

	i = -1;
	while (set->map[++i] != '\0')
	{
		x = (i % set->line_len) * 64;
		y = (i / set->line_len) * 64;
		mlx_put_image_to_window(set->mlx, set->win, set->imgs->tile, x, y);
		if (set->map[i] == '1')
			mlx_put_image_to_window(set->mlx, set->win, set->imgs->wall, x, y);
		else if (i == set->p)
			mlx_put_image_to_window(set->mlx, set->win, set->imgs->mot, x, y);
		else if (set->map[i] == 'C')
			mlx_put_image_to_window(set->mlx, set->win, set->imgs->coll, x, y);
		else if (set->map[i] == 'E')
			draw_exit(set, x, y);
	}
	return (0);
}

t_images	set_img(void *mlx_ptr)
{
	t_images	imgs;
	int			w;
	int			h;

	ft_memset(&imgs, 0, sizeof(imgs));
	imgs.mot = mlx_xpm_file_to_image(mlx_ptr, "./source/hero1.xpm", &w, &h);
	imgs.exit[0] = mlx_xpm_file_to_image(mlx_ptr, "./source/exit1.xpm", &w, &h);
	imgs.exit[1] = mlx_xpm_file_to_image(mlx_ptr, "./source/exit2.xpm", &w, &h);
	imgs.tile = mlx_xpm_file_to_image(mlx_ptr, "./source/tile.xpm", &w, &h);
	imgs.wall = mlx_xpm_file_to_image(mlx_ptr, "./source/wall.xpm", &w, &h);
	imgs.coll = mlx_xpm_file_to_image(mlx_ptr, "./source/coll.xpm", &w, &h);
	return (imgs);
}

void	draw_exit(t_set *set, int x, int y)
{
	if (set->coll_cnt == 1)
		mlx_put_image_to_window(set->mlx, set->win, set->imgs->exit[1], x, y);
	else
		mlx_put_image_to_window(set->mlx, set->win, set->imgs->exit[0], x, y);
}

int	initialize_set(t_set *set, t_images *img)
{
	int	win_width;
	int	win_height;

	win_width = set->line_len * 64;
	win_height = set->map_height * 64;
	set->mlx = mlx_init();
	set->win = mlx_new_window(set->mlx, win_width, win_height, "so_long");
	*img = set_img(set->mlx);
	set->imgs = img;
	return (0);
}

void	clear_game(t_set *set)
{
	if (check_flag(CLEAR_FLAG, set->flag) == -1)
		write(1, "GAME OVER\n", 10);
	else
		write(1, "GAME CLEAR\n", 11);
	exit(EXIT_SUCCESS);
}
