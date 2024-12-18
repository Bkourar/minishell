#include "minishell.h"

void	ft_unset(t_sh *cmd, t_env *env);

void	ft_unset(t_sh *cmd, t_env *env)
{
	t_env	*tmp;
	int		i;

	tmp = env;
	if (!cmd->args[1])
		return ;
	i = 1;
	while (cmd->args[i])
	{
		while (tmp)
		{
			if (ft_strncmp(cmd->args[i], tmp->var,
					ft_strlen(cmd->args[i]) + 1) == 0
				&& ft_strlen(cmd->args[i]) > 0)
			{
				ft_del_one(env, cmd->args[i]);
				break ;
			}
			tmp = tmp->next;
		}
		i++;
		tmp = env;
	}
	ft_hrb(1, 0);
}
