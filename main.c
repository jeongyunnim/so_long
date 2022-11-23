/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:51:04 by jeseo             #+#    #+#             */
/*   Updated: 2022/11/23 13:41:08 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

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
		perror("ERROR\nOPEN FAILURE\n");
		exit(EXIT_FAILURE);
	}
	ft_memset(&game, 0, sizeof(game));
	if (check_map(fd, &game) == ERROR || initialize_set(&game, &img) == ERROR)
		print_error(game);
	mlx_key_hook(game.win, key_handler, &game);
	mlx_loop_hook(game.mlx, draw_map, &game);
	mlx_hook(game.win, DESTROY, 0, destroy_handler, &game);
	mlx_loop(game.mlx);
	return (0);
}
