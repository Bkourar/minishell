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
	bool	logic;

	logic = false;
	if ((*nd)->tp == her_doc)
	{
		(*nd)->file_name = NULL;
		(*nd)->del = diformer(str, &logic);
		(*nd)->fd_her = open_here((*nd)->del, env, ft_strdup("eof"), &logic);
		if ((*nd)->fd_her == 1)
			return (change(nd), (*nd));
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

t_sh	*creat_commandline(t_sh **node, char *str, int *i)
{
	(*node)->args[*i] = ft_strdup(str);
	if (!(*node)->args[*i])
		return (NULL);
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

int	ft_lstsize_tk(t_tk *lst)
{
	int		i;
	t_tk	*node;

	node = lst;
	i = 0;
	while (node != NULL)
	{
		i++;
		node = node->nx;
	}
	return (i);
}
