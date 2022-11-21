/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 19:09:59 by jeseo             #+#    #+#             */
/*   Updated: 2022/11/21 22:30:24 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_map(int fd, t_set *set) // free 잘 해줬는지 체크
{
	int	count_temp;

	count_temp = 0;
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
	count_temp = set->coll_cnt + 1;
	find_route(set->check_map, set->p, &set->coll_cnt, set->line_len);
	if (set->coll_cnt != 0)
	{
		write(1, "ROUTE ERROR\n",12);
		return (ERROR);
	}
	set->coll_cnt = count_temp;
	write(1, "YOU CAN SOLVE! TRY! TRY!\n", 25);
	close(fd);
	return (0);
}

t_images	set_img(void *mlx_ptr)
{
	t_images	imgs;
	int			w;
	int			h;

	memset(&imgs, 0, sizeof(imgs));
	imgs.motion[0] = mlx_xpm_file_to_image(mlx_ptr, "./source/hero1.xpm", &w, &h);
	imgs.motion[1] = mlx_xpm_file_to_image(mlx_ptr, "./source/hero2.xpm", &w, &h);
	imgs.motion[2] = mlx_xpm_file_to_image(mlx_ptr, "./source/hero3.xpm", &w, &h);
	imgs.motion[3] = mlx_xpm_file_to_image(mlx_ptr, "./source/hero4.xpm", &w, &h);
	imgs.motion[4] = mlx_xpm_file_to_image(mlx_ptr, "./source/hero5.xpm", &w, &h);
	imgs.exit[0] = mlx_xpm_file_to_image(mlx_ptr, "./source/exit1.xpm", &w, &h);
	imgs.exit[1] = mlx_xpm_file_to_image(mlx_ptr, "./source/exit2.xpm", &w, &h);
	imgs.enm[0] = mlx_xpm_file_to_image(mlx_ptr, "./source/enm1.xpm", &w, &h);
	imgs.enm[1] = mlx_xpm_file_to_image(mlx_ptr, "./source/enm2.xpm", &w, &h);
	imgs.tile = mlx_xpm_file_to_image(mlx_ptr, "./source/tile.xpm", &w, &h);
	imgs.wall = mlx_xpm_file_to_image(mlx_ptr, "./source/wall.xpm", &w, &h);
	imgs.coll = mlx_xpm_file_to_image(mlx_ptr, "./source/coll.xpm", &w, &h);
	return (imgs);
}

int key_handler(int key_code, t_set *set)
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

void	make_enm(t_set *set)
{
	int 	i;
	char	locate;
	char	component;

	i = 0;

	while (set->check_map[i] != '\0')
	{
		locate = set->check_map[i];
		component = set->map[i];
		if (locate == '@' && component != 'C' && component != 'E' && i != set->p)
		{
			set->flag |= ENM_FLAG;
			set->e = i;
			set->map[i] = '@';
			return ;
		}
		i++;
	}
}

int	initialize_set(t_set *set, t_images *img)
{
	make_enm(set);
	set->mlx = mlx_init();
	set->win = mlx_new_window(set->mlx, set->line_len * 64, set->map_height * 64, "so_long");
	*img = set_img(set->mlx);
	set->imgs = img;
	set->move_count = ft_itoa(0);
	if (set->move_count == NULL)
		return (ERROR);
	return (0);
}

int	deley_n(int n)
{
	static unsigned int t;
	
	t++;
	return ((t/12) % n);
}

void draw_exit(t_set *set, int x, int y)
{
	if (set->coll_cnt == 1)
		mlx_put_image_to_window(set->mlx, set->win, set->imgs->exit[1], x, y);
	else
		mlx_put_image_to_window(set->mlx, set->win, set->imgs->exit[0], x, y);
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
			mlx_put_image_to_window(set->mlx, set->win, set->imgs->motion[deley_n(5)], x, y);
		else if (set->map[i] == 'C')
			mlx_put_image_to_window(set->mlx, set->win, set->imgs->coll, x, y);
		else if (set->map[i] == 'E')
			draw_exit(set, x, y);
		else if (set->map[i] == '@')
			mlx_put_image_to_window(set->mlx, set->win, set->imgs->enm[deley_n(2)], x, y);
	}
	mlx_string_put(set->mlx, set->win, 32, 64, 0x0, "move: ");
	mlx_string_put(set->mlx, set->win, 70, 64, 0x0, set->move_count);
	return (0);
}

int	destroy_handler(t_set *set)
{
	mlx_destroy_window(set->mlx, set->win);
	exit(EXIT_SUCCESS);
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

int	main(int argc, char **argv)
{
	int			fd;
	t_set		game;
	t_images	img;

	if (argc != 2)
		return (write(2, "ERROR\nARGUMENT COUNT ERROR\n", 27));
	if (check_extension(argv[1]) == ERROR)
		return (write(2, "ERROR\nFILENAME EXTENSION ERROR\n", 31));
	fd = open(argv[1], O_RDONLY);
	if (fd <= 0)
	{
		perror("OPEN FALURE\n");
		exit(EXIT_FAILURE);
	}
	ft_memset(&game, 0, sizeof(game));
	if (check_map(fd, &game) == ERROR || initialize_set(&game, &img) == ERROR)
	{
		write(2, "ERROR\nMAP CAN'T NOT BE DRAWN\n", 29);
		exit(EXIT_FAILURE);
	}
	mlx_key_hook(game.win, key_handler, &game);
	mlx_loop_hook(game.mlx, draw_map, &game);
	mlx_hook(game.win, DESTROY, 0, destroy_handler, &game);
	mlx_loop(game.mlx);
	return (0);
}
