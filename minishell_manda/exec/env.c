/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkacimi <abkacimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:29:16 by abkacimi          #+#    #+#             */
/*   Updated: 2024/10/14 12:16:17 by abkacimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_del_one(t_env *head, const char *var);
void	ft_set_it(t_env *env, const char *var, const char *new_value);
t_env	*parse_env(char **envir);
void	ft_show_env(t_env *env);

void	ft_del_one(t_env *head, const char *var)
{
	t_env	*t;
	t_env	*prev;

	prev = NULL;
	t = head;
	if (t != NULL && ft_strncmp(t->var, var, (ft_strlen(t->var) + 1)) == 0)
	{
		head = t->next;
		return ;
	}
	while (t != NULL && ft_strncmp(t->var, var, (ft_strlen(t->var) + 1)) != 0)
	{
		prev = t;
		t = t->next;
	}
	if (t == NULL)
		return ;
	prev->next = t->next;
}

void	ft_set_it(t_env *env, const char *var, const char *new_value)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(var, tmp->var, ft_strlen(var) + 1) == 0)
		{
			tmp->value = NULL;
			tmp->value = ft_sdup_ex(new_value);
		}
		tmp = tmp->next;
	}
}

t_env	*parse_env(char **envir)
{
	t_env	*h;
	char	*env;
	char	*eql;
	int		i;

	h = NULL;
	env_lst_back(&h, env_lstnew("", NULL));
	i = 0;
	while (envir[i])
	{
		env = envir[i];
		eql = ft_strchr(env, '=');
		if (eql)
		{
			*eql = '\0';
			env_lst_back(&h, env_lstnew(env, eql + 1));
			*eql = '=';
		}
		i++;
	}
	ft_save_pth(1);
	return (h);
}

void	ft_show_env(t_env *env)
{
	t_env	*e;

	e = env;
	while (e)
	{
		if (e->value)
		{
			ft_putstr_x(e->var, "=", e->value, 1);
			ft_putstr_x("\n", NULL, NULL, 1);
		}
		e = e->next;
	}
	ft_hrb(1, 0);
}

char	*get_value_e(t_env *env, char *var)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->var, var, ft_strlen(var)) == 0)
		{
			if (tmp->value)
				return (tmp->value);
			return ("");
		}
		tmp = tmp->next;
	}
	return (NULL);
}
