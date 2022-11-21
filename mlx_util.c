#include "so_long.h"

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

void draw_exit(t_set *set, int x, int y)
{
	if (set->coll_cnt == 1)
		mlx_put_image_to_window(set->mlx, set->win, set->imgs->exit[1], x, y);
	else
		mlx_put_image_to_window(set->mlx, set->win, set->imgs->exit[0], x, y);
}

int	destroy_handler(t_set *set)
{
	mlx_destroy_window(set->mlx, set->win);
	exit(EXIT_SUCCESS);
	return (0);
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