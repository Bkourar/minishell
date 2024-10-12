#include "minishell.h"

static void	switcher(char *c1, char *c2)
{
	*c1 = 'a';
	*c2 = 'n';
}


static void	rand_rot13(char *path)
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
	string = (char *)ft_allocate(1, ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!string)
		return (NULL);
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
	int		write_fd;
	int		read_fd;
	int		j;

	rand_rot13(c);
	c = join_path("/tmp", c);
	if (access(c, F_OK) == 0)
		return (switcher(&c[0], &c[4]), open_here(del, env, c, b));
	write_fd = open(c, O_CREAT | O_RDWR, 0666);
	read_fd = open(c, O_RDONLY);
	unlink(c);
	if (write_fd == -1 || read_fd == -1)
		perror("OPEN: ");
	j = pi_processing_here(write_fd, del, env, b);
	if (j == 1)
		return (close(write_fd), close(read_fd), j);
	(close(write_fd), fd_collector(0, read_fd));
	return (read_fd);
}
