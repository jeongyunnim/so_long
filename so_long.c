/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 19:09:59 by jeseo             #+#    #+#             */
/*   Updated: 2022/11/19 16:15:46 by jeseo            ###   ########.fr       */
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
	imgs.motion[0] = mlx_xpm_file_to_image(mlx_ptr, "./source/hero1.xpm", &width, &height);
	imgs.motion[1] = mlx_xpm_file_to_image(mlx_ptr, "./source/hero2.xpm", &width, &height);
	imgs.motion[2] = mlx_xpm_file_to_image(mlx_ptr, "./source/hero3.xpm", &width, &height);
	imgs.motion[3] = mlx_xpm_file_to_image(mlx_ptr, "./source/hero4.xpm", &width, &height);
	imgs.motion[4] = mlx_xpm_file_to_image(mlx_ptr, "./source/hero5.xpm", &width, &height);
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
		flag->move_count++;
	}
	if (key_code == D)
	{
		printf("D: %d\n", key_code);
		pressed_d(flag);
		flag->move_count++;
	}
	if (key_code == W)
	{
		printf("W: %d\n", key_code);
		pressed_w(flag);
		flag->move_count++;
	}
	if (key_code == A)
	{
		printf("A: %d\n", key_code);
		pressed_a(flag);
		flag->move_count++;
	}
	if (key_code == ESC)
	{
		printf("ESC: %d\n", key_code);
		pressed_esc();
	}
	return (0);
}

int mouse_handler(int button, int x, int y, t_set *set)
{
	printf("key: %d\n", button);
	printf("(x,y): (%d,%d)\n", x, y);
	free(set->check_map);
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

int	delay_motion(void)
{
	static int t;
	
	t++;
	//printf("t: %d\n",(t/20) % 5);
	return ((t/10) % 5);
}

int	draw_map(t_set *set)
{
	int			i;
	int			x;
	int			y;

	i = -1;
	while (set->map[++i] != '\0')
	{
		x = (i % set->line_len) * 64;
		y = (i / set->line_len) * 64;
		mlx_put_image_to_window(set->mlx, set->win, set->imgs->tile, x, y);
		if (set->map[i] == '1')
			mlx_put_image_to_window(set->mlx, set->win, set->imgs->wall, x, y);
		else if (i == set->p)
			mlx_put_image_to_window(set->mlx, set->win, set->imgs->motion[delay_motion()], x, y);
		else if (set->map[i] == 'C')
			mlx_put_image_to_window(set->mlx, set->win, set->imgs->coll, x, y);
		else if (set->map[i] == 'E')
			mlx_put_image_to_window(set->mlx, set->win, set->imgs->exit, x, y);
	}
	mlx_string_put(set->mlx, set->win, 32, 32, 0xFFFFFF, "move: ");
	return (0);
}

int	destroy_handler(t_set *set)
{
	mlx_destroy_window(set->mlx, set->win);
	exit(EXIT_SUCCESS);
	return (0);
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
	draw_map(&game);
	mlx_key_hook(game.win, key_handler, &game);
	mlx_mouse_hook(game.win, mouse_handler, &game);
	mlx_loop_hook(game.mlx, draw_map, &game);
	mlx_hook(game.win, 17, 0, destroy_handler, &game);
	mlx_loop(game.mlx);
	close(fd); //close 왜 해줘??
	return (0);
}
