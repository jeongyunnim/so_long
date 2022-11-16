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