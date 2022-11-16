/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 20:49:09 by jeseo             #+#    #+#             */
/*   Updated: 2022/11/16 19:36:14 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*ft_memset(void *bytes, int value, size_t len)
{
	unsigned char	*temp;

	temp = (unsigned char *)bytes;
	while (len > 0)
	{
		*temp = value;
		temp++;
		len--;
	}
	return (bytes);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t dest_size)
{
	size_t	i;

	i = 0;
	while (dest && i + 1 < dest_size)
	{
		dest[i] = src[i];
		i++;
	}
	if (dest_size > 0)
		dest[i] = '\0';
	return (0);
}

char	*ft_strnjoin(char **s1, char const *s2, size_t len)
{
	size_t	s1_len;
	char	*res;

	res = NULL;
	s1_len = 0;
	while (*s1 && (*s1)[s1_len])
		s1_len++;
	res = (char *)malloc((s1_len + len + 1) * sizeof(char));
	if (res == NULL)
	{
		if (*s1)
			free(*s1);
		return (NULL);
	}
	if (*s1)
	{
		ft_strlcpy(res, *s1, s1_len + 1);
		free(*s1);
	}
	ft_strlcpy(res + s1_len, s2, len + 1);
	return (res);
}
