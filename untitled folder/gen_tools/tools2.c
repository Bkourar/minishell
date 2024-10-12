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

int	strnlcpy(char **dst, unsigned int *j,char *src, char c)
{
	unsigned int	i;
	int				l;

	i = 0;
	l = 0;
	if (src[i] == c)
		(*dst)[*j] = src[i];
	src[i] = ' ';
	(counter((int *)j, 1), counter((int *)(&i), 1));
	while (src[i])
	{
		if (src[i] == c)
			break ;
		(*dst)[*j] = src[i];
		src[i] = ' ';
		(counter((int *)j, 1), counter((int *)(&i), 1));
	}
	if (src[i] == c)
		(*dst)[*j] = src[i];
	src[i] = ' ';
	(counter((int *)j, 1), counter((int *)(&i), 1));
	l = i;
	return (l);
}