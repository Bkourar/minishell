#include "minishell.h"

void	ft_start_exec(t_sh **cmd, t_env **env);
void	init_d(t_data *dt, t_sh *cmd);
void	ft_restorefds(t_data *dt);

// void	print_them_all(t_sh *cc)
// {
// 	t_sh *cmd = cc;
// 	while(cmd)
// 	{
// 		int i = 0;
// 		while(cmd->args[i])
// 		{
// 			printf("{%s}\n", cmd->args[i]);
// 			i++;
// 		}
// 		while(cmd->dir)
// 		{
// 			printf("%d : %s\n", cmd->dir->tp, cmd->dir->file_name);
// 			cmd->dir = cmd->dir->next;
// 		}
// 		if (cmd->next)
// 			printf("-------there is next \n");
// 		cmd = cmd->next;
// 	}
// 	printf("\n\n");
// }

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

void	ft_start_exec(t_sh **cmd, t_env **env)
{
	t_data	dt;
	char	**pth;

	pth = environnement_pth(*env);
	init_d(&dt, *cmd);
	if (its_bult((*cmd)->args[0]) == 11 && dt.cnt == 1)
	{
		handle_redirections((*cmd)->dir, 1);
		execute_builtin(*cmd, *env);
		ft_restorefds(&dt);
		return ;
	}
	while (cmd && *cmd)
	{
		main_exec(&dt, *cmd, *env, pth);
		*cmd = (*cmd)->next;
		dt.i++;
	}
	waitpid(dt.pids[dt.cnt -1], &dt.status, 0);
	while (wait(0) > 0)
		;
	if (WIFEXITED(dt.status))
		ft_hrb(1, WEXITSTATUS(dt.status));
	ft_restorefds(&dt);
	fd_collector(36, 123);
}

void	ft_restorefds(t_data *dt)
{
	ft_signal();
	dup2(dt->std_in, 0);
	close(dt->std_in);
	dup2(dt->std_out, 1);
	close(dt->std_out);
}
