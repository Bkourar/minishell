/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkacimi <abkacimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:29:24 by abkacimi          #+#    #+#             */
/*   Updated: 2024/10/22 16:17:40 by abkacimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_exec(t_data *dt, t_sh *cmd, t_env *env, char **path);
void	final_ex(t_sh *cmd, t_env *env, char *pth);
void	deal_with_chp(t_data *dt, t_sh *cmd, char *pth, t_env *env);
void	deal_with_pp(t_data *dt, t_sh *cmd);

void	main_exec(t_data *dt, t_sh *cmd, t_env *env, char **path)
{
	char	*pth;

	if (cmd->args[0] == NULL)
		return ;
	pth = get_path(path, cmd->args[0]);
	if (cmd->next && pipe(dt->fd) == -1)
		(write(2, "pipe\n", 5), exit(ft_hrb(1, 127)));
	dt->pids[dt->i] = fork();
	if (dt->pids[dt->i] < 0)
		(write(2, "fork\n", 5), exit(ft_hrb(1, 127)));
	else if (dt->pids[dt->i] == 0)
		deal_with_chp(dt, cmd, pth, env);
	if (dt->pids[dt->i] != 0)
		deal_with_pp(dt, cmd);
}

void	deal_with_chp(t_data *dt, t_sh *cmd, char *pth, t_env *env)
{
	if (dt->i > 0)
	{
		dup2(dt->save, 0);
		close(dt->save);
	}
	if (cmd->next)
	{
		close(dt->fd[0]);
		dup2(dt->fd[1], 1);
	}
	else
	{
		dup2(dt->std_out, 1);
		close(dt->std_out);
	}
	final_ex(cmd, env, pth);
}

void	deal_with_pp(t_data *dt, t_sh *cmd)
{
	if (dt->i > 0)
		close(dt->save);
	if (cmd->next)
	{
		close(dt->fd[1]);
		dt->save = dt->fd[0];
	}
}

void	final_ex(t_sh *cmd, t_env *env, char *pth)
{
	handle_redirections(cmd->dir, 0);
	if (its_bult(cmd->args[0]) == 11)
	{
		execute_builtin(cmd, env);
		exit(ft_hrb(1, 0));
	}
	else
	{
		execve(pth, cmd->args, env_to_arr(env, 0));
		if (just_cmd(cmd->args[0]) == 1)
		{
			ft_putstr_x(cmd->args[0], ": command not found\n", NULL, 2);
			exit(ft_hrb(1, 127));
		}
		else
		{
			ft_putstr_x(cmd->args[0], ": No such file or directory\n", NULL, 2);
			exit(ft_hrb(1, 126));
		}
	}
}
