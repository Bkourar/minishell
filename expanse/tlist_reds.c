#include "minishell.h"

void	ft_lstadd_back_dir(t_dir **lst, t_dir *new)
{
	t_dir	*temp;

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

int	ft_lstsiz_dir(t_dir *lst)
{
	int		i;
	t_dir	*node;

	node = lst;
	i = 0;
	while (node != NULL)
	{
		i++;
		node = node->next;
	}
	return (i);
}

t_dir	*config_redirect(char *in, int j, t_dir *nd)
{
	t_dir	*new;

	new = (t_dir *)malloc(sizeof(t_dir));
	if (!new)
		return (write(2, "faile allocation\n", 18), NULL);
	new->par = (t_par *)malloc(sizeof(t_par));
	if (!new->par)
		return (write(2, "faile allocation\n", 18), NULL);
	if (in == NULL)
		new->input = NULL;
	else
	{
		new->input = ft_strdup(in);
		if (!new->input)
			return (write(2, "faile allocation\n", 18), NULL);
	}
	new->par->st = nd->par->st;
	new->par->tp = nd->par->tp;
	new->par->wd = nd->par->wd;
	new->ambg = j;
	new->next = NULL;
	return (new);
}

static void	upgrade_parameter(t_par **setting, int rwx)
{
	if (rwx == 4 || rwx == 6 || rwx == 5 || rwx == 7)
		(*setting)->tp = exp;
	else
		(*setting)->tp = not_exp;
	if (rwx == 2 || rwx == 6 || rwx == 3 || rwx == 7)
		(*setting)->wd = wrd;
	else
		(*setting)->wd = not_wrd;
	if (rwx == 1 || rwx == 5 || rwx == 3 || rwx == 7)
		(*setting)->st = join;
	else
		(*setting)->st = not_join;
}

t_dir	*upgrade_redirect(char *in, int *chmod, int j)
{
	t_dir	*new;

	new = (t_dir *)malloc(sizeof(t_dir));
	if (!new)
		return (write(2, "faile allocation\n", 18), NULL);
	new->par = (t_par *)malloc(sizeof(t_par));
	if (!new->par)
		return (write(2, "faile allocation\n", 18), NULL);
	upgrade_parameter(&new->par, *chmod);
	new->input = ft_strdup(in);
	if (!new->input)
		return (write(2, "faile allocation\n", 18), NULL);
	new->ambg = j;
	new->ck = 0;
	new->next = NULL;
	return (new);
}