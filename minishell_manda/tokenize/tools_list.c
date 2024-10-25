/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bikourar <bikourar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:24:21 by bikourar          #+#    #+#             */
/*   Updated: 2024/10/22 12:11:16 by bikourar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back_msh(t_sh **lst, t_sh *new)
{
	t_sh	*temp;

	if (!(*lst))
	{
		(*lst) = new;
		return ;
	}
	temp = (*lst);
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
}

void	ft_lstadd_redir(t_redir **lst, t_redir *new)
{
	t_redir	*temp;

	if (!(*lst))
	{
		(*lst) = new;
		return ;
	}
	temp = (*lst);
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
}

t_redir	*creat_node(char *str, t_redir **nd, t_env **env)
{
	BOOL	logic;

	logic = FALSE;
	if ((*nd)->tp == her_doc)
	{
		(*nd)->file_name = NULL;
		(*nd)->del = diformer(str, &logic);
		(*nd)->fd_her = open_here((*nd)->del, env, ft_strdup("eof"), &logic);
		if ((*nd)->fd_her == 1)
			return (change(nd, TRUE), (*nd));
	}
	else
	{
		if (str == NULL)
			(*nd)->file_name = NULL;
		else
		{
			(*nd)->del = NULL;
			(*nd)->file_name = str;
		}
		(*nd)->fd_her = -1;
	}
	(*nd)->next = NULL;
	return ((*nd));
}

t_sh	*creat_cmdline(t_sh **node, char *str, int *i)
{
	(*node)->args[*i] = ft_strdup(str);
	if (!(*node)->args[*i])
		return (write(2, "faile allocation\n", 18), NULL);
	return (*node);
}

int	ft_lstsize(t_sh *lst)
{
	int		i;
	t_sh	*node;

	node = lst;
	i = 0;
	while (node != NULL)
	{
		i++;
		node = node->next;
	}
	return (i);
}
