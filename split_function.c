/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeseo <jeseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 20:30:19 by jeseo             #+#    #+#             */
/*   Updated: 2022/11/16 20:30:20 by jeseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_flag(char flag, char target)
{
	if ((flag & target) == 0)
	{
		return (-1);
	}
	else
		return (0);
}

void	free_string(char **target)
{
	if (*target != NULL)
		free(*target);
	*target = NULL;
}