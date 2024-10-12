#include "minishell.h"

t_exp	*config(char *in)
{
	t_exp	*new;

	new = (t_exp *)ft_allocate(1, sizeof(t_exp));
	if (!new)
		return (write(2, "faile allocation\n", 18), NULL);
	new->set = (t_set *)ft_allocate(1, sizeof(t_set));
	if (!new->set)
		return (write(2, "faile allocation\n", 18), NULL);
	new->input = ft_strdup(in);
	if (new->input == NULL)
		return (write(2, "faile allocation\n", 18), NULL);
	new->set->sp = 0;
	new->set->st = 0;
	new->set->tp = 0;
	new->next = NULL;
	return (new);
}

int	ft_lstsize_exp(t_exp *lst)
{
	int		i;
	t_exp	*node;

	node = lst;
	i = 0;
	while (node != NULL)
	{
		i++;
		node = node->next;
	}
	return (i);
}

void	ft_lstadd_back_texp(t_exp **lst, t_exp *new)
{
	t_exp	*temp;

	if (new == NULL)
		return ;
	if (!(*lst))
	{
		(*lst) = new;
		new->prv = NULL; 
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	new->prv = temp; 
}

t_exp	*upgrade_input(char *in, int *chmod)
{
	t_exp	*new;

	new = (t_exp *)ft_allocate(1, sizeof(t_exp));
	if (!new)
		return (write(2, "faile allocation\n", 18), NULL);
	new->set = (t_set *)ft_allocate(1, sizeof(t_set));
	if (!new->set)
		return (write(2, "faile allocation\n", 18), NULL);
	upgrade_setting(&new->set, *chmod);
	new->input = ft_strdup(in);
	if (new->input == NULL)
		return (write(2, "faile allocation\n", 18), NULL);
	new->next = NULL;
	return (new);
}

t_exp	*ft_lstlast_exp(t_exp **lst)
{
	t_exp	*tmp;

	if (!lst)
		return (NULL);
	tmp = *lst;
	while (tmp != NULL)
	{
		if (tmp->next == NULL)
			break;
		tmp = tmp->next;
	}
	return (tmp);
}
