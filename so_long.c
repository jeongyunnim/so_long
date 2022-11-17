/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 19:09:59 by jeseo             #+#    #+#             */
/*   Updated: 2022/11/17 17:24:07 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// void	esc_event(void *mlx_ptr, void *win_ptr)
// {
// 	mlx_destroy_window(mlx_ptr, win_ptr);
// }

int	check_map(int fd) // free 잘 해줬는지 체크
{
	t_flags	flags;
	char	*map_line;
	char	*map;

	memset(&flags, 0, sizeof(flags));
	map = NULL;
	map_line = NULL;
	while (check_flag(END_FLAG, flags.flag) == -1)
	{
		map_line = get_next_line(fd);
		if (map_line == NULL)
			flags.flag |= END_FLAG;
		else if (check_line(map_line, &flags) != ERROR)
		{
			map = ft_strnjoin(&map, map_line, flags.line_len);
			if (map == NULL)
				return (ERROR);
			flags.map_height++;
		}
		else
			return (ERROR);
		free_string(&map_line);
	}
	printf("map: %s\n", map);
	if (check_components(map, flags) == ERROR)
		return (ERROR);
	find_route(map, flags.p, &flags.coll_cnt, flags.line_len);
	printf("find_map: %s\n", map);
	if (flags.coll_cnt != 0)
	{
		write(1, "ROUTE ERROR\n",12);
		write(1, "IT CAN'T BE SOLVED\n", 19);
		return (ERROR);
	}
	else
	{
		write(1, "YOU CAN SOLVE! TRY! TRY!\n", 24);
		if (open_and_draw(map, flags) == ERROR)
			return (ERROR);
	}
	return (0);
}

t_images	pack_img(void *mlx_ptr)
{
	t_images	imgs;
	int			width;
	int			height;

	memset(&imgs, 0, sizeof(imgs));
	imgs.tile = mlx_xpm_file_to_image(mlx_ptr, "./source/tile.xpm", &width, &height);
	imgs.wall = mlx_xpm_file_to_image(mlx_ptr, "./source/wall.xpm", &width, &height);
	imgs.coll = mlx_xpm_file_to_image(mlx_ptr, "./source/coll.xpm", &width, &height);
	imgs.hero = mlx_xpm_file_to_image(mlx_ptr, "./source/hero.xpm", &width, &height);
	imgs.exit = mlx_xpm_file_to_image(mlx_ptr, "./source/tile.xpm", &width, &height); // 왜 포인터만을 사용해야 하는지..??
	return (imgs);
}

void	initialize_map(void *mlx_ptr, void *win_ptr, void *tile, t_flags flag)
{
	int		i;
	int		j;

	i = -1;
	while (++i < flag.map_height)
	{
		j = -1;
		while (++j < flag.line_len)
			mlx_put_image_to_window(mlx_ptr, win_ptr, tile, 64 * j, 64 * i);
	}
}

int	open_and_draw(char *map, t_flags flag)
{
	t_images	images;
	void		*mlx_ptr;
	void		*win_ptr;
	int			i;

	i = -1;
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, flag.line_len * 64, flag.map_height * 64, "test"); // 왜 -1 해주는지?
	images = pack_img(mlx_ptr);
	initialize_map(mlx_ptr, win_ptr, images.tile, flag);
	printf("%s\n", map);
	while (map[++i] != '\0')
	{
		if (map[i] == '1')
			mlx_put_image_to_window(mlx_ptr, win_ptr, images.wall, (i % flag.line_len) * 64, (i / flag.line_len) * 64);
		else if (map[i] == 'C')
			mlx_put_image_to_window(mlx_ptr, win_ptr, images.coll, (i % flag.line_len) * 64, (i / flag.line_len) * 64);
		else if (map[i] == 'P')
			mlx_put_image_to_window(mlx_ptr, win_ptr, images.hero, (i % flag.line_len) * 64, (i / flag.line_len) * 64);
		else if (map[i] == 'E')
			mlx_put_image_to_window(mlx_ptr, win_ptr, images.exit, (i % flag.line_len) * 64, (i / flag.line_len) * 64);
	}
	mlx_loop(mlx_ptr);
	return (0);
}

int	main(int argc, char **argv)
{
	int		fd;

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
	if (check_map(fd) == ERROR)
	{
		close(fd);
		return (write(2, "ERROR\nIT CAN'T BE SOLVED\n", 25));//perror?
	}
	close(fd); //close 왜 해줘??
	return (0);
}
