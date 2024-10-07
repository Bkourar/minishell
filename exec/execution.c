#include "minishell.h"

void	ft_start_exec(t_sh **cmd, t_env **env);
void	init_d(t_data *dt, t_sh *cmd);

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
// 		// while(cmd->dir)
// 		// {
// 		// 	printf("ok\n");
// 		// 	printf("%d : %d : ", cmd->dir->tp, cmd->dir->fd_her);
// 		// 	printf("%s\n", cmd->dir->file_name);
// 		// 	cmd->dir = cmd->dir->next;
// 		// }
// 		if (cmd->next)
// 			printf("\nthere is next \n");
// 		cmd = cmd->next;
// 	}
// 	// exit(1);
// }

void	init_d(t_data *dt, t_sh *cmd)
{
	dt->cnt = ft_lstsize(cmd);
	dt->std_in = dup(0);
	dt->std_out = dup(1);
	dt->save = 0;
	dt->i = 0;
	dt->pids = malloc(sizeof(int) * (dt->cnt + 1));
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
	// print_them_all(*cmd);
	if (its_bult((*cmd)->args[0]) == 11 && dt.cnt == 1)
	{
		execute_builtin(*cmd, *env);
		return ;
	}
	while (cmd && *cmd)
	{
		main_exec(&dt, *cmd, *env, pth);
		*cmd = (*cmd)->next;
		dt.i++;
	}
	waitpid(dt.pids[dt.cnt], &dt.status, 0);
	while (wait(0) > 0);
	ft_hrb(1, WEXITSTATUS(dt.status)), ft_signal();
	free(dt.pids);
	dup2(dt.std_in, 0);
	close(dt.std_in);
	dup2(dt.std_out, 1);
	close(dt.std_out);
}
