/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultins.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkacimi <abkacimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:28:48 by abkacimi          #+#    #+#             */
/*   Updated: 2024/10/21 11:49:42 by abkacimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		its_bult(char *cmd);
void	execute_builtin(t_sh *cmd, t_env *env);

int	its_bult(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", 5))
		return (11);
	else if (!ft_strncmp(cmd, "cd", 3))
		return (11);
	else if (!ft_strncmp(cmd, "export", 7))
		return (11);
	else if (!ft_strncmp(cmd, "pwd", 4))
		return (11);
	else if (!ft_strncmp(cmd, "env", 4) || !ft_strncmp(cmd, "ENV", 4))
		return (11);
	else if (!ft_strncmp(cmd, "exit", 5))
		return (11);
	else if (!ft_strncmp(cmd, "unset", 6))
		return (11);
	return (27);
}

void	execute_builtin(t_sh *cmd, t_env *env)
{
	if (!ft_strncmp(cmd->args[0], "echo", 5))
		build_echo(cmd->args, 1);
	else if (!ft_strncmp(cmd->args[0], "cd", 3))
		change_directory(cmd, env);
	else if (!ft_strncmp(cmd->args[0], "export", 7))
		build_export(cmd, env);
	else if (!ft_strncmp(cmd->args[0], "pwd", 4))
		ft_pwd();
	else if (!ft_strncmp(cmd->args[0], "env", 4)
		|| !ft_strncmp(cmd->args[0], "ENV", 4))
	{
		if (!cmd->args[1])
			ft_show_env(env);
		else
		{
			ft_putstr_x("env : ", cmd->args[1],
				": No such file or directory\n", 2);
			ft_hrb(1, 127);
		}
	}
	else if (!ft_strncmp(cmd->args[0], "exit", 5))
		ft_exit(cmd);
	else if (!ft_strncmp(cmd->args[0], "unset", 6))
		ft_unset(cmd, env);
}
