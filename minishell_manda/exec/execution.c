/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bikourar <bikourar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:29:30 by abkacimi          #+#    #+#             */
/*   Updated: 2024/10/25 17:16:33 by bikourar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_start_exec(t_sh **cmd, t_env **env);
void	init_d(t_data *dt, t_sh *cmd);
void	ft_restorefds(t_data *dt);

void	print_them_all(t_sh *cc)
{
	t_sh *cmd = cc;
	while(cmd)
	{
		int i = 0;
		while(cmd->args[i])
		{
			printf("[%s]\n", cmd->args[i]);
			i++;
		}
		// while(cmd->dir)
		// {
		// 	printf("%d : {%s}\n", cmd->dir->tp, cmd->dir->file_name);
		// 	cmd->dir = cmd->dir->next;
		// }
		// if (cmd->next)
		// 	printf("-------there is next \n");
		cmd = cmd->next;
	}
	printf("\n\n");
}

static int	check_argument(t_sh *tp)
{
	t_redir	*p;

	if (!*tp->args)
	{
		p = tp->dir;
		while (p)
		{
			if (check_te(p->tp))
				return (1);
			p = p->next;
		}
	}
	return (0);
}

static t_sh	*modify_args(t_sh **cm)
{
	t_redir	*p;
	BOOL	l;

	if (!*(*cm)->args)
	{
		l = FALSE;
		p = (*cm)->dir;
		while (p)
		{
			if (check_te(p->tp))
				l = TRUE;
			p = p->next;
		}
		if (l == TRUE)
			(*cm)->args[0] = NULL;
	}
	return ((*cm));
}

void	init_d(t_data *dt, t_sh *cmd)
{
	dt->cnt = ft_lstsize(cmd);
	dt->save = 0;
	dt->std_in = dup(0);
	dt->std_out = dup(1);
	dt->i = 0;
	dt->pids = ft_allocate(1, sizeof(int) * (dt->cnt + 1));
	if (!dt->pids)
	{
		write(2, "malloc", 7);
		exit(ft_hrb(1, 1));
	}
}

void	js_red(t_data *dt, t_sh *cmd)
{
	if (cmd->next && pipe(dt->fd) == -1)
		(write(2, "pipe\n", 5), exit(ft_hrb(1, 127)));
	dt->pids[dt->i] = fork();
	if (dt->pids[dt->i] < 0)
		(write(2, "fork\n", 5), exit(ft_hrb(1, 127)));
	else if (dt->pids[dt->i] == 0)
	{
		if (dt->i > 0)
			(dup2(dt->save, 0), close(dt->save));
		if (cmd->next)
			(close(dt->fd[0]), dup2(dt->fd[1], 1));
		else
			(dup2(dt->std_out, 1), close(dt->std_out));
		(handle_redirections(cmd->dir, 1), exit(ft_hrb(0, 0)));
	}
	else
		deal_with_pp(dt, cmd);
}

void	ft_start_exec(t_sh **cmd, t_env **env)
{
	t_data	dt;
	char	**pth;

	print_them_all(*cmd);
	pth = environnement_pth(*env);
	init_d(&dt, *cmd);
	if (its_bult((*cmd)->args[0]) == 11 && dt.cnt == 1)
	{
		handle_redirections((*cmd)->dir, 1);
		(execute_builtin(*cmd, *env), ft_restorefds(&dt));
		return ;
	}
	while (cmd && *cmd)
	{
		if ((*cmd)->args[0] && ft_strcmp((*cmd)->args[0], "./minishell"))
			signal_child();
		if (check_argument(*cmd))
		{
			(*cmd) = modify_args(cmd);
			(js_red(&dt, *cmd), nxt(cmd), addp(&dt.i, 1));
			continue ;
		}
		(main_exec(&dt, *cmd, *env, pth), nxt(cmd), addp(&dt.i, 1));
	}
	(ischild(1, TRUE), waitpid(dt.pids[dt.cnt -1], &dt.status, 0));
	ft_fnsh(&dt);
}
