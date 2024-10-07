#include "minishell.h"

int	count_wd(char **spliting)
{
	int	i;

	i = 0;
	if (!spliting)
		return (0);
	while (spliting[i])
		i++;
	return (i);
}

