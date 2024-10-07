#include "minishell.h"

static int	long_nl(char const *str, char del)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (i);
	while (str[i] != del && str[i])
		i++;
	return (i);
}

static int	str_cmp(char *buf, char *limiter)
{
	int	a;

	a = 0;
	if (limiter == NULL)
		return (0);
	while (buf[a] && buf[a] != '\n' && limiter[a] && limiter[a] == buf[a])
		a++;
	if (long_nl(limiter, '\0') == long_nl(buf, '\n')
		&& long_nl(limiter, '\0') == a)
		return (1);
	return (0);
}

static int	loop_inf(int fd, char *del, t_env **env, bool *b)
{
	char	*buff;

	while (1)
	{
		buff = NULL;
		buff = readline("> ");
		if (buff == NULL)
			break ;
		if (str_cmp(buff, del) == 1)
			break ;
		if (*b == false && buff[0] != '\0')
		{
			buff = join_arg(pi_processing_expand(buff, env));
			if (buff == NULL)
				return (1);
		}
		write(fd, buff, long_nl(buff, '\n') + 1), write(fd, "\n", 1);
		free(buff);
	}
	return (0);
}

void	pi_processing_here(int	fd, char *dilemiter, t_env **env, bool *b)
{
	pid_t	id;

	signal(SIGINT, SIG_IGN);
	id = fork();
	if (id == 0)
	{
		signal_heredoc();
		if (loop_inf(fd, dilemiter, env, b))
			exit(ft_hrb(1, EXIT_FAILURE));
		else
			exit(ft_hrb(1, EXIT_SUCCESS));
	}
	else if (id == -1)
		(perror("Fork failed"), exit(EXIT_FAILURE));
	wait(NULL);
	ft_signal();
}

