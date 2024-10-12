#include "minishell.h"

void	*ft_allocate(int flag, int size);
void	gc_free(t_g *head);
void	ft_bzero_x(void *s, int size);
t_g		*gc_new(int size);
void	gc_addback(t_g **lst, t_g *new);

void	*ft_allocate(int flag, int size)
{
	static t_g	*head;
	t_g			*node;

	if (flag == 36)
	{
		gc_free(head);
		head = NULL;
		return (NULL);
	}
	else
	{
		node = gc_new(size);
		ft_bzero_x(node->ptr, size);
		gc_addback(&head, node);
		return (node->ptr);
	}
}

void	gc_free(t_g *head)
{
	t_g	*h;
	t_g	*tmp;

	h = head;
	if (!head)
		return ;
	while (h)
	{
		tmp = h->next;
		free(h->ptr);
		free(h);
		h = tmp;
	}
	h = NULL;
	tmp = NULL;
	head = NULL;
}

void	ft_bzero_x(void *s, int size)
{
	int		i;
	char	*b;

	i = 0;
	b = (char *)s;
	while (i < size)
	{
		b[i] = 0;
		i++;
	}
}

t_g	*gc_new(int size)
{
	t_g	*node;

	node = (t_g *)malloc(sizeof(t_g));
	if (!node)
		return (NULL);
	node->ptr = malloc(size);
	node->next = NULL;
	return (node);
}

void	gc_addback(t_g **lst, t_g *new)
{
	t_g	*temp;

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
