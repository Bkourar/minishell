/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bikourar <bikourar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:15:34 by abkacimi          #+#    #+#             */
/*   Updated: 2024/10/25 16:54:08 by bikourar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_all(void)
{
	ft_allocate(36, 0);
	fd_collector(36, 0);
}

static int	nul(void *arg, BOOL b, char *rd, t_redir *dir)
{
	g_sig_heredoc = 0;
	if (b == TRUE && arg == NULL && dir == NULL)
		return (free(rd), free_all(), 1);
	else if (b == FALSE && !arg && dir == NULL)
		return (free(rd), free_all(), 1);
	else if (b == FALSE && !arg && dir && dir->tp == her_doc)
		return (free(rd), free_all(), 1);
	return (0);
}

static int	mt_or_only_sp(char *str)
{
	if (!str || str[0] == '\0')
		return (3);
	while (*str)
	{
		if (!w_sp(*str))
			return (22);
		str++;
	}
	return (3);
}

static t_tk	*parse_line(char *line, int ac, char **av)
{
	char	**shell_line;
	t_tk	*tok;

	(void)ac;
	(void)av;
	tok = NULL;
	shell_line = NULL;
	if ((mt_or_only_sp(line)) == 3)
		return (NULL);
	shell_line = token_input(line, &tok);
	if (!shell_line)
		return (NULL);
	tok = create_commands(shell_line);
	if (!tok)
		return (write(2, "fail allocation\n", 17), NULL);
	tok = pi_processing_cmd(&tok);
	if (!tok)
		return (NULL);
	return (tok);
}

int	main(int ac, char **av, char **env)
{
	struct termios	termios;
	t_tk			*prs;
	t_sh			*cl;
	t_env			*ev;
	char			*rd;

	ev = parse_env(env);
	(tcgetattr(STDIN_FILENO, &termios), ft_signal());
	while (1)
	{
		rl_catch_signals = 0;
		tcsetattr(STDIN_FILENO, TCSANOW, &termios);
		cl = NULL;
		rd = readline("bash-1.2.1$ ");
		if (!rd)
			break ;
		(add_history(rd), TRUE) && (prs = parse_line(rd, ac, av));
		if (nul(prs, TRUE, rd, NULL))
			continue ;
		cl = token_data(rd, ev, &cl);
		if (nul(cl, TRUE, rd, NULL) || nul(cmt(cl, 1), FALSE, rd, cmt(cl, 0)))
			continue ;
		(free(rd), ft_start_exec(&cl, &ev), ft_allocate(36, 0));
	}
	(write(2, "exit\n", 6), exit(ft_hrb(0, 0)));
}
