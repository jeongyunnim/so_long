/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 19:09:59 by jeseo             #+#    #+#             */
/*   Updated: 2022/11/18 21:34:59 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_map(int fd, t_set *set) // free 잘 해줬는지 체크
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
	if (check_components(set) == ERROR)
		return (ERROR);
	set->check_map = strdup(set->map);
	if (set->check_map == NULL)
		return (ERROR);
	find_route(set->check_map, set->p, &set->coll_cnt, set->line_len);
	free_string(&set->check_map);
	printf("find_map: %s\n", set->map);
	if (set->coll_cnt != 0)
	{
		write(1, "ROUTE ERROR\n",12);
		write(1, "IT CAN'T BE SOLVED\n", 19);
		return (ERROR);
	}
	write(1, "YOU CAN SOLVE! TRY! TRY!\n", 24);
	return (0);
}

t_images	set_img(void *mlx_ptr)
{
	t_images	imgs;
	int			width;
	int			height;

	memset(&imgs, 0, sizeof(imgs));
	imgs.motion1 = mlx_xpm_file_to_image(mlx_ptr, "./source/hero1.xpm", &width, &height);
	imgs.motion2 = mlx_xpm_file_to_image(mlx_ptr, "./source/hero2.xpm", &width, &height);
	imgs.motion3 = mlx_xpm_file_to_image(mlx_ptr, "./source/hero3.xpm", &width, &height);
	imgs.motion4 = mlx_xpm_file_to_image(mlx_ptr, "./source/hero4.xpm", &width, &height);
	imgs.motion5 = mlx_xpm_file_to_image(mlx_ptr, "./source/hero5.xpm", &width, &height);
	imgs.tile = mlx_xpm_file_to_image(mlx_ptr, "./source/tile.xpm", &width, &height);
	imgs.wall = mlx_xpm_file_to_image(mlx_ptr, "./source/wall.xpm", &width, &height);
	imgs.coll = mlx_xpm_file_to_image(mlx_ptr, "./source/coll.xpm", &width, &height);
	imgs.exit = mlx_xpm_file_to_image(mlx_ptr, "./source/tile.xpm", &width, &height);
	return (imgs);
}

// void	draw_tile(t_set set, void *tile)
// {
// 	int		i;
// 	int		j;

// 	i = -1;
// 	while (++i < set.map_height)
// 	{
// 		j = -1;
// 		while (++j < set.line_len)
// 			mlx_put_image_to_window(set.mlx, set.win, tile, 64 * j, 64 * i);
// 	}
// }

int key_handler(int key_code, t_set *flag)
{
	if (key_code == S)
	{
		printf("S: %d\n", key_code);
		pressed_s(flag);
	}
	if (key_code == D)
	{
		printf("D: %d\n", key_code);
		pressed_d(flag);
	}
	if (key_code == W)
	{
		printf("W: %d\n", key_code);
		pressed_w(flag);
	}
	if (key_code == A)
	{
		printf("A: %d\n", key_code);
		pressed_a(flag);
	}
	if (key_code == ESC)
	{
		printf("ESC: %d\n", key_code);
		pressed_esc();
	}
	return (0);
}

int	initialize_set(t_set *set, t_images *img)
{
	set->mlx = mlx_init();
	set->win = mlx_new_window(set->mlx, set->line_len * 64, set->map_height * 64, "so_long");
	*img = set_img(set->mlx);
	set->imgs = img;
	return (0);
}

void	draw_map(t_set set, t_images img)
{
	int	i;
	int	x;
	int	y;

	i = -1;
	while (set.map[++i] != '\0')
	{
		x = (i % set.line_len) * 64;
		y = (i / set.line_len) * 64;
		mlx_put_image_to_window(set.mlx, set.win, img.tile, x, y);
		if (set.map[i] == '1')
			mlx_put_image_to_window(set.mlx, set.win, img.wall, x, y);
		else if (i == set.p)
			mlx_put_image_to_window(set.mlx, set.win, img.motion1, x, y);
		else if (set.map[i] == 'C')
			mlx_put_image_to_window(set.mlx, set.win, img.coll, x, y);
		else if (set.map[i] == 'E')
			mlx_put_image_to_window(set.mlx, set.win, img.exit, x, y);
	}
}

int	main(int argc, char **argv)
{
	int			fd;
	t_set		game;
	t_images	img;

	if (argc != 2)
		return (write(2, "ERROR\n", 6));
	//if (argv[1] != "*.ber")
	//	return (write(2, "ERROR\n", 6));
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		write(2, "OPEN FALURE", 11);
		exit(EXIT_FAILURE);
	}
	memset(&game, 0, sizeof(game));
	if (check_map(fd, &game) == ERROR)
	{
		close(fd);
		return (write(2, "ERROR\nIT CAN'T BE SOLVED\n", 25));//perror?
	}
	initialize_set(&game, &img);
	draw_map(game, img);
	mlx_key_hook(game.win, key_handler, &game);
	mlx_string_put(game.mlx, game.win, 32, 32, 0xFFFFFF, "GO TO HEEEEEEEELLLO");
	mlx_loop(game.mlx);
	close(fd); //close 왜 해줘??
	return (0);
}
