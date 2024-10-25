/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkacimi <abkacimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 21:16:32 by abkacimi          #+#    #+#             */
/*   Updated: 2024/10/22 21:17:29 by abkacimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_spcl_red(int flag)
{
	ft_putstr_x(NULL, "... : No such file or directory\n", NULL, 2);
	if (flag == 0)
		exit(ft_hrb(1, 1));
	ft_hrb(1, 1);
}

void	ft_restorefds(t_data *dt)
{
	ft_signal();
	dup2(dt->std_in, 0);
	close(dt->std_in);
	dup2(dt->std_out, 1);
	close(dt->std_out);
}

void	show_prblm(char *file, int prblm, int flag)
{
	if (prblm == 1)
		ft_putstr_x(file, "... : No such file or directory\n", NULL, 2);
	else if (prblm == 2)
		ft_putstr_x(file, " : Permission denied \n", NULL, 2);
	else if (prblm == 3)
		ft_putstr_x(file, " : Is a directory\n", NULL, 2);
	else if (prblm == 4)
		ft_putstr_x(file, ": Unknown error\n", NULL, 2);
	if (flag == 0)
		exit(ft_hrb(1, 1));
	ft_hrb(1, 1);
}
