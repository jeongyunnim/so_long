/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 20:48:24 by jeseo             #+#    #+#             */
/*   Updated: 2022/11/21 22:26:38 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "./mlx/mlx.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>

# define BUFFER_SIZE	100
# define ERROR			-1

/*변화를 알 때 효율적*/
# define WALL_FLAG	0x01 // 0000 0001
# define HERO_FLAG	0x02 // 0000 0010
# define COLL_FLAG	0x04 // 0000 0100
# define EXIT_FLAG	0x08 // 0000 1000
# define RECT_FLAG	0x10 // 0001 0000
# define END_FLAG	0x20 // 0010 0000
# define CLEAR_FLAG	0x40 // 0100 0000
# define ENM_FLAG	0x80 // 1000 0000

/*key code*/
# define W			13
# define S			1
# define A			0
# define D			2
# define ESC		53
# define DESTROY	17

typedef struct s_images
{
	void	*motion[5];
	void	*exit[2];
	void	*enm[2];
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
	char		*move_count;
	int			map_height;
	int			line_len;
	int			coll_cnt;
	int			p;
	int			e;
	char		flag;
}	t_set;

char	*ft_itoa(int n);
void	*ft_calloc(size_t n, size_t size);

size_t	ft_strlcpy(char *dest, const char *src, size_t dest_size);
void	*ft_memset(void *bytes, int value, size_t len);
void	free_string(char **target);
char	*ft_strnjoin(char **s1, char const *s2, size_t len);
char	*get_next_line(int fd);

void	find_route(char *map, int current, int *collectable, int width);
int		draw_map(t_set *set);
int		check_line(t_set *set);
int		check_components(t_set *flag);
int		check_flag(char flag, char target);

int			initialize_set(t_set *set, t_images *img);
t_images	set_img(void *mlx_ptr);

void	pressed_wasd(int keycode, t_set *set);
void	pressed_esc(void);
void	print_error(char flag);

void	clear_game(t_set *set);

#endif