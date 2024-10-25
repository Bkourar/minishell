/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkacimi <abkacimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:29:53 by abkacimi          #+#    #+#             */
/*   Updated: 2024/10/13 15:29:53 by abkacimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		*gc_env(int flag, int size);
void		gc_free_env(t_gc_e *hd);
void		bzero_env(void *s, int size);
t_gc_e		*gc_env_new(int size);
void		gc_env_add_b(t_gc_e **lst, t_gc_e *new);

void	*gc_env(int flag, int size)
{
	static t_gc_e	*hd;
	t_gc_e			*nd;

	if (flag == 36)
	{
		gc_free_env(hd);
		hd = NULL;
		return (NULL);
	}
	else
	{
		nd = gc_env_new(size);
		bzero_env(nd->ptr, size);
		gc_env_add_b(&hd, nd);
		return (nd->ptr);
	}
}

void	gc_free_env(t_gc_e *hd)
{
	t_gc_e	*h;
	t_gc_e	*tmp;

	h = hd;
	if (!hd)
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
	hd = NULL;
}

void	bzero_env(void *s, int size)
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

t_gc_e	*gc_env_new(int size)
{
	t_gc_e	*nd;

	nd = (t_gc_e *)malloc(sizeof(t_gc_e));
	if (!nd)
		return (NULL);
	nd->ptr = malloc(size);
	nd->next = NULL;
	return (nd);
}

void	gc_env_add_b(t_gc_e **lst, t_gc_e *new)
{
	t_gc_e	*temp;

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
