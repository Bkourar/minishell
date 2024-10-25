/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkacimi <abkacimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:29:11 by abkacimi          #+#    #+#             */
/*   Updated: 2024/10/13 15:29:11 by abkacimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_lstnew(const char *var, const char *value);
void	env_lst_back(t_env **lst, t_env *new);
int		count_env_vars(t_env *env);
char	**env_to_arr(t_env *env, int i);
char	**environnement_pth(t_env *e);

t_env	*env_lstnew(const char *var, const char *value)
{
	t_env	*new_node;

	new_node = (t_env *)gc_env(1, sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->var = ft_sdup_ex(var);
	new_node->value = ft_sdup_ex(value);
	new_node->next = NULL;
	return (new_node);
}

void	env_lst_back(t_env **lst, t_env *new)
{
	t_env	*temp;

	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

int	count_env_vars(t_env *env)
{
	t_env	*temp;
	int		count;

	temp = env;
	count = 0;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

char	**env_to_arr(t_env *env, int i)
{
	int		cnt;
	t_env	*temp;
	char	*joined_str;
	char	*temp_var;
	char	**arr;

	cnt = count_env_vars(env);
	arr = (char **)ft_allocate(1, (cnt + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	temp = env;
	while (i < cnt)
	{
		temp_var = exec_join(ft_strdup(temp->var), "=");
		joined_str = exec_join(temp_var, temp->value);
		arr[i] = joined_str;
		temp = temp->next;
		i++;
	}
	arr[cnt] = NULL;
	return (arr);
}

char	**environnement_pth(t_env *e)
{
	char	**arr;

	arr = NULL;
	while (e)
	{
		if (ft_strncmp(e->var, "PATH", 5) == 0)
		{
			arr = ft_ex_splt(e->value, ':');
		}
		e = e->next;
	}
	return (arr);
}
