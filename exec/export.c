#include "minishell.h"

void	build_export(t_sh *cmd, t_env *env);
void	ft_bmaz(char *var, char *val, t_env *env, int flag);
void	exprt_prs(char *cmd, t_env *env, int i);

void	ft_bmaz(char *var, char *val, t_env *env, int flag)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(var, tmp->var, ft_strlen(var)) == 0)
		{
			if (flag == 0 && val != NULL)
				ft_set_it(env, var, val);
			else
				ft_set_it(env, var, safe_join(tmp->value, val));
			break ;
		}
		tmp = tmp->next;
	}
	if (!tmp)
	{
		env_lst_back(&env, env_lstnew(var, val));
	}
}

void	exprt_prs(char *cmd, t_env *env, int i)
{
	int		flag;
	char	*var;
	char	*val;

	i = 0;
	flag = 0;
	while (cmd[i] && cmd[i] != '=')
		i++;
	if (cmd[i] == '=')
	{
		if (cmd[i - 1] == '+')
		{
			flag = 27;
			var = ft_substr(cmd, 0, i - 1);
			val = ft_substr(cmd, i + 2, ft_strlen(cmd));
		}
		else
		{
			var = ft_substr(cmd, 0, i);
			val = ft_substr(cmd, i + 1, ft_strlen(cmd));
		}
		ft_bmaz(var, val, env, flag);
	}
	else
		ft_bmaz(cmd, NULL, env, 0);
}

int	valid_x_arg(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] != '_' && ft_isalpha(arg[i]) == 0)
	{
		return (ft_putstr_x("export: ",
				arg, ": not a valid identifier\n", 2), 0);
	}
	while (arg[i] && (arg[i] == '_' || ft_isalnum(arg[i])))
		i++;
	if (arg[i] == '=' || (arg[i] == '+' && arg[i + 1] && arg[i + 1] == '='))
		return (1);
	if (arg[i] == '\0')
		return (1);
	else if (arg[i] != '_' && ft_isalpha(arg[i]) == 0)
	{
		return (ft_putstr_x("export: ",
				arg, ": not a valid identifier\n", 2), 0);
	}
	return (1);
}

void	exp_no_args(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strlen(tmp->var))
		{
			ft_putstr_x("declare -x ", tmp->var, NULL, 1);
			if (tmp->value != NULL)
			{
				ft_putstr_x("=\"", tmp->value, "\"", 1);
			}
			ft_putstr_x("\n", NULL, NULL, 1);
		}
		tmp = tmp->next;
	}
}

void	build_export(t_sh *cmd, t_env *env)
{
	int	i;

	i = 1;
	if (!cmd->args[1])
	{
		return (exp_no_args(env));
	}
	else
	{
		while (cmd->args[i])
		{
			if (valid_x_arg(cmd->args[i]) == 1)
			{
				exprt_prs(cmd->args[i], env, 0);
			}
			i++;
		}
	}
}
