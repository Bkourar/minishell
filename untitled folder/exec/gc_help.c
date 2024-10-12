#include "minishell.h"

char	*new_j(char const *s1, char const *s2)
{
	char	*string;
	int		i;
	int		j;

	j = 0;
	if (!s1 && !s2)
		return (string = NULL, NULL);
	else if (!s1)
		return (ft_sdup_ex(s2));
	else if (!s2)
		return (ft_sdup_ex(s1));
	string = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!string)
		return (free((char *)s2), NULL);
	i = 0;
	while (s1[i])
		string[j++] = s1[i++];
	i = 0;
	while (s2[i])
		string[j++] = s2[i++];
	string[j] = '\0';
	return (string);
}

char	*ft_sdup_ex(char const *src)
{
	char	*destion;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (src == NULL)
		return (NULL);
	destion = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!destion)
		return (write(2, "faile allocation\n", 18), NULL);
	while (src[i])
		destion[j++] = src[i++];
	destion[j] = '\0';
	return (destion);
}
