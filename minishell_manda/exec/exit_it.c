/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_it.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkacimi <abkacimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:29:34 by abkacimi          #+#    #+#             */
/*   Updated: 2024/10/21 12:29:40 by abkacimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_hrb(int flag, int stt);
int		valid_exit(char *str);
void	ft_exit(t_sh *cmd);
void	ft_fnsh(t_data *dt);

int	ft_hrb(int flag, int stt)
{
	static int	x;

	if (flag == 1)
		x = stt;
	return (x);
}

int	valid_exit(char *str)
{
	while (*str && (*str == '\t' || *str == ' '))
		str++;
	if (*str == '\0')
		return (0);
	if (*str == '+' || *str == '-')
		str++;
	if (!(*str >= '0' && *str <= '9'))
		return (0);
	while (*str && (*str >= '0' && *str <= '9'))
		str++;
	while (*str && (*str == '\t' || *str == ' '))
		str++;
	if (*str == '\0')
		return (1);
	return (0);
}

void	ft_exit(t_sh *cmd)
{
	ft_putstr_x("exit\n", NULL, NULL, 2);
	if (!cmd->args[1])
		exit(ft_hrb(0, 0));
	else
	{
		if (valid_exit(cmd->args[1]) == 0)
		{
			ft_putstr_x("exit :",
				cmd->args[1], ": numeric argument required\n", 2);
			exit(ft_hrb(1, 255));
		}
		else if (cmd->args[2])
		{
			ft_putstr_x("exit: too many arguments\n", NULL, NULL, 2);
			ft_hrb(1, 1);
		}
		else
			exit(atoll_x(cmd->args[1]));
	}
}

void	ft_fnsh(t_data *dt)
{
	while (wait(0) > 0)
		;
	if (WIFEXITED(dt->status))
		ft_hrb(1, WEXITSTATUS(dt->status));
	ft_signal();
	dup2(dt->std_in, 0);
	close(dt->std_in);
	dup2(dt->std_out, 1);
	close(dt->std_out);
	ischild(1, FALSE);
	fd_collector(36, 123);
}
