#include "minishell.h"

int	ft_strcmp(char const *s1, char const *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i] && s2[j] && s1[i] == s2[j])
	{
		i++;
		j++;
	}
	return (s1[i] - s2[j]);
}

char	*ft_strdup(char const *src)
{
	char	*destion;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (src == NULL)
		return (NULL);
	destion = (char *)malloc(ft_strlen(src) + 1);
	if (!destion)
		return (write(2, "faile allocation\n", 18) ,NULL);
	while (src[i])
		destion[j++] = src[i++];
	destion[j] = '\0';
	return (destion);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*string;
	int		i;
	int		j;

	j = 0;
	if (!s1 && !s2)
		return (string = NULL, NULL);
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	string = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!string)
		return (free((char *)s2),NULL);
	i = 0;
	while (s1[i])
		string[j++] = s1[i++];
	i = 0;
	while (s2[i])
		string[j++] = s2[i++];
	string[j] = '\0';
	return (free((char *)s1), string);
}

size_t	ft_strlen(const char *theString)
{
	size_t	i;

	if (!theString)
		return (0);
	i = 0;
	while (theString[i])
		i++;
	return (i);
}

char	*ft_strncpy(char *dst, char *src, int index)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (src[i] && i < (unsigned int)index)
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	dst[j] = '\0';
	return (dst);
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
