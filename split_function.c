#include "so_long.h"

int	check_flag(char flag, char target)
{
	if (flag & target == 0)
		return (0);
	else
		return (-1);
}

void	free_all(void **target)
{
	if (*target != NULL)
		free(*target);
	*target = NULL;
}