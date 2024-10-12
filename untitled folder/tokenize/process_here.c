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
	char	*bf;
	char	*s;

	while (1)
	{
		s = readline("> ");
		bf = ft_strdup(s);
		free(s);
		if ((bf == NULL) || (str_cmp(bf, del) == 1))
			break ;
		if ((*b) == false && bf[0] != '\0')
		{
			bf = join_arg(pi_processing_expand(bf, env, *b));
			if (bf == NULL)
				return (1);
			(write(fd, bf, long_nl(bf, '\n') + 1), write(fd, "\n", 1));
		}
		else
			(write(fd, bf, long_nl(bf, '\n') + 1), write(fd, "\n", 1));
	}
	return (0);
}

int	pi_processing_here(int	fd, char *dilemiter, t_env **env, bool *b)
{
	pid_t	id;
	int		status;

	// signal(SIGINT, SIG_IGN);
	id = fork();
	if (id == -1)
		(perror("Fork failed"), exit(EXIT_FAILURE));
	else if (id == 0)
	{
		// signal_heredoc();
		if (loop_inf(fd, dilemiter, env, b))
		{
			ft_allocate(36, 0);	
			exit(ft_hrb(1, EXIT_FAILURE));
		}
		else
		{	
			ft_allocate(36, 0);	
			exit(ft_hrb(1, EXIT_SUCCESS));
		}
	}
	wait(&status);//, ft_signal();
	if (WIFEXITED(status))
		ft_hrb(1, WEXITSTATUS(status));
	if (ft_hrb(0, 0) == EXIT_FAILURE)
		return (1);
	return (0);
}
