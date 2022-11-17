/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 20:48:24 by jeseo             #+#    #+#             */
/*   Updated: 2022/11/17 17:27:53 by jeseo            ###   ########.fr       */
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
# define END_FLAG	0x10 // 0001 0000

typedef struct s_flagss
{
	int		map_height;
	int		line_len;
	int		coll_cnt;
	int		p;
	char	flag;
}	t_flags;

typedef struct s_map
{
	char	*map_line;
	char	*map;
	char	*map_check;
}	t_map;

typedef struct s_images
{
	void	*tile;
	void	*wall;
	void	*coll;
	void	*hero;
	void	*exit;
}	t_images;

t_images	pack_img(void *mlx_ptr);

void	*ft_memset(void *bytes, int value, size_t len);
void	free_string(char **target);

char	*ft_strnjoin(char **s1, char const *s2, size_t len);
char	*get_next_line(int fd);

int		check_line(char *map, t_flags *flags);
int	check_components(char *map, t_flags flag);
int		check_flag(char flag, char target);
int		open_and_draw(char *map, t_flags flag);
void	find_route(char *map, int current, int *collectable, int width);

size_t	ft_strlcpy(char *dest, const char *src, size_t dest_size);


#endif