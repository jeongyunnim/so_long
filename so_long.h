/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 20:48:24 by jeseo             #+#    #+#             */
/*   Updated: 2023/01/16 15:32:22 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "./mlx/mlx.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# define BUFFER_SIZE	200
# define ERROR			-1

# define WALL_FLAG	0x01
# define HERO_FLAG	0x02
# define COLL_FLAG	0x04
# define EXIT_FLAG	0x08
# define RECT_FLAG	0x10
# define END_FLAG	0x20
# define CLEAR_FLAG	0x40
# define ENM_FLAG	0x80

# define W			13
# define S			1
# define A			0
# define D			2
# define ESC		53
# define KEY_UP		3
# define MOUSE_DOWN	4
# define DESTROY	17

typedef struct s_images
{
	void	*mot;
	void	*exit[2];
	void	*tile;
	void	*wall;
	void	*coll;
}	t_images;

typedef struct s_settings
{
	t_images	*imgs;
	void		*mlx;
	void		*win;
	char		*map;
	char		*check_map;
	int			map_height;
	int			line_len;
	int			coll_cnt;
	int			p;
	int			e;
	char		flag;
}	t_set;

typedef struct s_getline
{
	char	buff[BUFFER_SIZE + 1];
	char	*line;
	int		flag;
}	t_getline;

char		*ft_itoa(int n);
void		*ft_calloc(size_t n, size_t size);
char		*ft_strdup(const char *str);
size_t		ft_strlcpy(char *dest, const char *src, size_t dest_size);
void		*ft_memset(void *bytes, int value, size_t len);
char		*ft_strnjoin(char **s1, char const *s2, size_t len);
size_t		ft_strlen(const char *str);

char		*get_next_line(int fd);

void		free_string(char **target);
int			deley_n(int n);

t_images	set_img(void *mlx_ptr);
int			initialize_set(t_set *set, t_images *img);
int			draw_map(t_set *set);
void		draw_exit(t_set *set, int x, int y);
void		print_move_cnt(t_set *set, int move_cnt);

int			check_valid(t_set *set);
int			check_line(t_set *set);
int			check_components(t_set *flag);
int			check_flag(char flag, char target);
int			check_map(int fd, t_set *set);
int			check_extension(char *target);
void		find_route(char *map, int current, int *collectable, int width);

void		pressed_wasd(int keycode, t_set *set);
void		movement(t_set *set, char current, int move, char who);
void		pressed_esc(void);
void		print_error(t_set set);
void		clear_game(t_set *set);
int			destroy_handler(t_set *set);
int			key_handler(int key_code, t_set *set);

#endif