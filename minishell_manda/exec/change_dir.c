/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkacimi <abkacimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:28:58 by abkacimi          #+#    #+#             */
/*   Updated: 2024/10/22 21:01:50 by abkacimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_directory(t_sh *cmd, t_env *env);
void	ft_change_that(t_env *env, char *var, char *new);
void	go_to_save(void);
void	cd_home(t_env *env);
void	change_cwd(char *c_pth, t_env *env);

void	change_directory(t_sh *cmd, t_env *env)
{
	if (!cmd->args[1])
		cd_home(env);
	else
		change_cwd(cmd->args[1], env);
}

void	go_to_save(void)
{
	ft_hrb(1, 0);
	chdir(ft_save_pth(0));
}

void	ft_change_that(t_env *env, char *var, char *new)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(var, tmp->var, ft_strlen(var)) == 0)
		{
			tmp->value = ft_sdup_ex(new);
		}
		tmp = tmp->next;
	}
}

void	cd_home(t_env *env)
{
	ft_hrb(1, 0);
	while (env)
	{
		if ((ft_strncmp(env->var, "HOME", 5) == 0))
		{
			if (!env->value)
				ft_putstr_x("bash: cd: HOME not set\n", NULL, NULL, 2);
			else
			{
				if (chdir(env->value) == -1)
					ft_putstr_x("cd:", env->value,
						": No such file or directory\n", 2);
				else
				{
					ft_change_that(env, "PWD", env->value);
					ft_hrb(1, 0);
				}
			}
			ft_hrb(1, 1);
			return ;
		}
		env = env->next;
	}
	ft_putstr_x("bash: cd: HOME not set\n", NULL, NULL, 2);
	ft_hrb(1, 1);
}

void	change_cwd(char *c_pth, t_env *env)
{
	char	old_pwd[PATH_MAX];
	char	pwd[PATH_MAX];
	char	cwd[PATH_MAX];

	ft_strlcpy(old_pwd, ft_get_cwd(), PATH_MAX);
	if (getcwd(pwd, PATH_MAX) == NULL && ft_strncmp(c_pth, "..", 3) == 0)
	{
		go_to_save();
		ft_change_that(env, "PWD", ft_save_pth(0));
		ft_hrb(1, 0);
	}
	else if (chdir(c_pth) == -1)
	{
		if (errno == ENOENT)
			ft_putstr_x("cd: ", c_pth, ": No such file or directory\n", 2);
		else if (errno == EACCES)
			ft_putstr_x("cd: ", c_pth, ": Permission denied\n", 2);
		else if (errno == ENOTDIR)
			ft_putstr_x("cd: ", c_pth, ": Not a directory\n", 2);
		else
			ft_putstr_x("cd: ", c_pth, ": Error accessing directory\n", 2);
		ft_hrb(1, 1);
	}
	ft_strlcpy(cwd, ft_get_cwd(), PATH_MAX);
	(ft_change_that(env, "OLDPWD", old_pwd), ft_change_that(env, "PWD", cwd));
}
