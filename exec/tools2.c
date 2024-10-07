#include "minishell.h"

int		ft_isdigit(char c);
int		ft_isalpha(char c);
int		ft_isalnum(char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	return (0);
}

int	ft_isalpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

int	ft_isalnum(char c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_sdup_ex(""));
	if (start + len > ft_strlen(s))
		len = ft_strlen(s) - start;
	str = (char *)ft_allocate(1, len + 1);
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[len] = '\0';
	return (str);
}
char	*ft_sdup_ex(char const *src)
{
	char	*dst;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!src)
		return (NULL);
	dst = (char *)ft_allocate(1, ft_strlen(src) + 1);
	if (!dst)
		return (NULL);
	while (src[i])
		dst[j++] = src[i++];
	dst[j] = '\0';
	return (dst);
}
