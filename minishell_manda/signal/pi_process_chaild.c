/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pi_process_chaild.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bikourar <bikourar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:28:06 by bikourar          #+#    #+#             */
/*   Updated: 2024/10/24 22:46:59 by bikourar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ctrl_nline_quit(int sig)
{
	if (sig == SIGINT)
		(printf ("\n"), ft_hrb(1, 130));
	else if (sig == SIGQUIT)
		(printf("Quit: %d\n", sig), ft_hrb(1, 131));
}

void	signal_child(void)
{
	signal(SIGQUIT, ctrl_nline_quit);
	signal(SIGINT, ctrl_nline_quit);
}
