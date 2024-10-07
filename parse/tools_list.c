#include "minishell.h"

void	ft_lstadd_back_ttk(t_tk **lst, t_tk *new)
{
	t_tk	*temp;

	if (lst == NULL)
		return ;
	if (!(*lst))
	{
		(*lst) = new;
		new->pv = NULL;
		return ;
	}
	temp = *lst;
	while (temp->nx)
		temp = temp->nx;
	temp->nx = new;
	new->pv = temp;
}

t_tk	*ft_lstlast(t_tk **lst)
{
	t_tk	*tmp;

	if (!lst)
		return (NULL);
	tmp = *lst;
	while (tmp != NULL)
	{
		if (tmp->nx == NULL)
			break;
		tmp = tmp->nx;
	}
	return (tmp);
}

t_tk	*ft_lstnew(char *content, bool b)
{
	t_tk	*n_node;

	n_node = (t_tk *)malloc(sizeof(t_tk));
	if (!n_node)
		return (NULL);
	if (b == true)
		n_node->checker = 0;
	n_node->token = ft_strdup(content);
	if (!n_node->token)
		return (NULL);
	n_node->nx = NULL;
	return (n_node);
}

// void	free_arr(char **arg)
// {
// 	int	i;

// 	i = 0;
// 	while (arg[i])
// 		free(arg[i++]);
// 	free(arg);
// }

// void	free_tok(t_tk **l)
// {
// 	t_tk	*tp1;
// 	t_tk	*tp2;

// 	tp1 = (*l);
// 	tp2 = tp1->nx;
// 	while (tp2)
// 	{
// 		free(tp1->token);
// 		free(tp1->stat);
// 		free(tp1);
// 		tp1 = tp2;
// 		tp2 = tp2->nx;
// 	}
// 	free(tp1->stat);
// 	free(tp1->token);
// 	free(tp1);
// }