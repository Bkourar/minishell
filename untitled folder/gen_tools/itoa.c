#include "minishell.h"

static int	check(long number)
{
	long	i;
	int		j;

	i = 1;
	j = 0;
	if (number <= 0)
	{
		if (number < 0)
			number *= -1;
		j++;
	}
	while (number / i > 0)
	{
		i *= 10;
		j++;
	}
	return (j);
}

static char	*dynamic(long number, int j)
{
	char	*str;

	str = (char *)ft_allocate(1, sizeof(char) * (j + 1));
	if (!str)
		return (NULL);
	str[j--] = '\0';
	if (number <= 0)
	{
		if (number < 0)
		{
			str[0] = '-';
			number = -number;
		}
		else
			str[j--] = '0';
	}
	while (number)
	{
		str[j--] = (number % 10) + '0';
		number /= 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	long	nbr;
	int		i;

	nbr = (long)n;
	i = check(nbr);
	return (dynamic(nbr, i));
}

// char	*f_strjoin(char const *s1, char const *s2)
// {
// 	char	*string;
// 	int		i;
// 	int		j;

// 	j = 0;
// 	if (!s1 && !s2)
// 		return (string = NULL, NULL);
// 	else if (!s1)
// 		return (ft_strdup(s2));
// 	else if (!s2)
// 		return (ft_strdup(s1));
// 	string = (char *)ft_allocate(1, ft_strlen(s1) + ft_strlen(s2) + 2);
// 	if (!string)
// 		return (//free((char *)s2), NULL);
// 	i = 0;
// 	while (s1[i])
// 		string[j++] = s1[i++];
// 	i = 0;
// 	while (s2[i])
// 		string[j++] = s2[i++];
// 	string[j] = '\0';
// 	return (//free((char *)s1), string);
// }