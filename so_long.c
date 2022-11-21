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
	if (check_components(set) == ERROR || check_valid(set) == ERROR)
		return (ERROR);
	set->check_map = strdup(set->map);
	if (set->check_map == NULL)
		return (ERROR);
	write(1, "YOU CAN SOLVE! TRY! TRY!\n", 25);
	close(fd);
	return (0);
}

int	check_valid(t_set *set)
{
	int		count_temp;
	char	check_map[set->map_height * set->line_len + 1];

	count_temp = 0;
	count_temp = set->coll_cnt + 1;
	ft_strlcpy(check_map, set->map, set->map_height * set->line_len + 1); 
	find_route(check_map, set->p, &set->coll_cnt, set->line_len);
	if (set->coll_cnt != 0)
	{
		write(1, "ROUTE ERROR\n",12);
		return (ERROR);
	}
	set->coll_cnt = count_temp;
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
	// t_images	img;

	if (argc != 2)
		return (write(2, "ERROR\nARGUMENT COUNT ERROR\n", 27));
	if (check_extension(argv[1]) == ERROR)
		return (write(2, "ERROR\nFILENAME EXTENSION ERROR\n", 31));
	fd = open(argv[1], O_RDONLY);
	if (fd <= 0)
	{
		perror("OPEN FAILURE\n");
		exit(EXIT_FAILURE);
	}
	ft_memset(&game, 0, sizeof(game));
	
	if (check_map(fd, &game) == ERROR)
	{
		print_error(game.flag);
		exit(EXIT_FAILURE);
	}
/*	m1 compile issue
	if (check_map(fd, &game) == ERROR || initialize_set(&game, &img) == ERROR)
	{
		write(2, "ERROR\nMAP CAN'T NOT BE DRAWN\n", 29);
		exit(EXIT_FAILURE);
	}
	mlx_key_hook(game.win, key_handler, &game);
	mlx_loop_hook(game.mlx, draw_map, &game);
	mlx_hook(game.win, DESTROY, 0, destroy_handler, &game);
	mlx_loop(game.mlx);
*/
	return (0);
}
