/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_here.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bikourar <bikourar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:23:04 by bikourar          #+#    #+#             */
/*   Updated: 2024/10/24 23:10:37 by bikourar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static int	loop_inf(int fd, char *del, t_env **env, BOOL *b)
{
	char	*bf;
	char	*rd;

	while (1)
	{
		bf = NULL;
		rd = readline("> ");
		(bf = ft_strdup(rd)) && (free(rd), TRUE);
		if (bf == NULL || (str_cmp(bf, del) == 1))
			break ;
		if ((*b) == FALSE && bf[0] != '\0')
		{
			bf = join_arg(pi_processing_expand(bf, env, *b));
			if (bf == NULL)
				continue ;
			(write(fd, bf, long_nl(bf, '\n') + 1), write(fd, "\n", 1));
		}
		else
			(write(fd, bf, long_nl(bf, '\n') + 1), write(fd, "\n", 1));
	}
	return (0);
}

int	pi_processing_here(int fd, char *dilemiter, t_env **env, BOOL *b)
{
	pid_t	id;
	int		status;

	if (g_sig_heredoc == 1)
		return (1);
	else
		ischild(1, TRUE);
	signal(SIGINT, SIG_IGN);
	id = fork();
	if (id == 0)
	{
		signal_heredoc();
		if (loop_inf(fd, dilemiter, env, b))
			exit(EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	else if (id == -1)
		(perror("Fork failed"), exit(ft_hrb(1, EXIT_FAILURE)));
	(ischild(1, FALSE), wait(&status), ft_signal());
	if (WIFEXITED(status))
		ft_hrb(1, WEXITSTATUS(status));
	if (ft_hrb(0, 0) == EXIT_FAILURE)
		return (g_sig_heredoc = 1, ischild(1, FALSE), 1);
	return (g_sig_heredoc = 0, 0);
}

void	chos(t_e *i, int j)
{
	*i = j;
}
