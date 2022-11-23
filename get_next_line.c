/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 19:18:09 by jeseo             #+#    #+#             */
/*   Updated: 2022/11/22 17:49:43 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

static void	save_buff(char **save, char *buff, size_t i)
{
	if (i == BUFFER_SIZE)
		**save = '\0';
	else
		ft_strlcpy(*save, buff, BUFFER_SIZE - i + 1);
}

static char	*ret_line(char *dest, char *src, char *save, int *flag)
{
	size_t	len;
	char	*line;

	len = 0;
	while (src[len] != '\n' && src[len] != '\0')
		len++;
	if (src[len] == '\n')
	{
		len++;
		*flag = 1;
	}
	else if (src[len] == '\0' && len < BUFFER_SIZE && !*save)
		*flag = 1;
	line = ft_strnjoin(&dest, src, len);
	save_buff(&save, src + len, len);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	save[BUFFER_SIZE + 1];
	t_getline	ret;

	ft_memset(&ret, 0, sizeof(ret));
	while (fd > 0)
	{
		ft_memset(ret.buff, 0, BUFFER_SIZE + 1);
		if (*save != 0)
		{
			ret.line = ret_line(ret.line, save, save, &(ret.flag));
			if (ret.line == NULL)
				return (NULL);
		}
		else if (read(fd, ret.buff, BUFFER_SIZE) <= 0)
			break ;
		else
		{
			ret.line = ret_line(ret.line, ret.buff, save, &(ret.flag));
			if (ret.line == NULL)
				return (NULL);
		}
		if (ret.flag == 1)
			return (ret.line);
	}
	return (ret.line);
}
