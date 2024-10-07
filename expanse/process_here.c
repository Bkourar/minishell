#include "minishell.h"

char	*rand_rot13(char *path)
{
	int		i;

	i = 0;
	while (path[i])
	{
		if ((path[i] >= 'a' && path[i] < 'm') || (path[i] >= 'A' && path[i] < 'M'))
			path[i] = path[i] + 13;
		else if ((path[i] >= 'n' && path[i] < 'z') || (path[i] >= 'N' && path[i] < 'Z'))
			path[i] = path[i] - 13;
		i++;
	}
	return (path);
}

static char	*join_path(char const *s1, char const *s2)
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
		return (free((char *)s2), NULL);
	i = 0;
	while (s1[i])
		string[j++] = s1[i++];
	string[j++] = '/';
	i = 0;
	while (s2[i])
		string[j++] = s2[i++];
	string[j] = '\0';
	return (string);
}

int	open_here(char *del, t_env **env, char *c, bool *b)
{
	int		fd = 0;

	if (fd == 0 && del[0] != '\0' && c == NULL)
		c = ft_strdup(del);
	else
		c = ft_strdup("eof");
	c = rand_rot13(c);
	c = join_path("/tmp", c);
	if (access(c, F_OK) == 0)
	{
		c[0] = 'a';
		c[4] = 'z';
		open_here(del, env, c, b);
	}
	else
	{
		fd = open(c, O_CREAT | O_WRONLY , 0222);
		if (fd == -1)
			perror("OPEN: ");
		pi_processing_here(fd, del, env, b), close(fd);
		fd = open(c, O_RDONLY, 0444);
	}
	if (unlink(c) == -1)
		perror("UNLINK: ");
	return (free(c), fd);
}
