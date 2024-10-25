/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pi_process_signal.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bikourar <bikourar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:27:36 by bikourar          #+#    #+#             */
/*   Updated: 2024/10/24 22:52:16 by bikourar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ctrl_c_newline(int sig)
{
	if (ischild(0, TRUE) == TRUE)
	{
		puts("222");
		return ;
	}
	if (sig == SIGINT)
	{
		ft_hrb(1, 1);
		printf ("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_signal(void)
{
	rl_catch_signals = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ctrl_c_newline);
}

static void	ctrl_c_line(int sig)
{
	(void)sig;
	printf ("\n");
	exit(EXIT_FAILURE);
}

void	signal_heredoc(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ctrl_c_line);
}
