#include "minishell.h"

void	counter(int *counter, int val)
{
	*counter = *counter + val;
}

char	*ck_and_dp(char c)
{
	char	*dst;
	char	c1[2];

	dst = NULL;
	if (c == '\'')
		c1[0] = '\'';
	else if (c == '\"')
		c1[0] = '\"';
	c1[1] = '\0';
	dst = ft_strdup(c1);
	if (!dst)
		return (write(2, "faile allocation\n", 18), NULL);
	return (dst);
}

char	*dup_quote(char *str, int *i, char c)
{
	char	*dst;
	int		j;

	dst = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!dst)
		write(2, "faile allocation\n", 18), exit(1);
	if (str[*i] == c)
		*i += 1;
	j = 0;
	while (str[*i])
	{
		if (str[*i] == c)
		{
			break ;
		}
		dst[j++] = str[*i];
		*i += 1;
	}
	return (dst[j] = '\0', dst);
}