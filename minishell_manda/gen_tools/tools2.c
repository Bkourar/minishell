/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bikourar <bikourar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:30:14 by bikourar          #+#    #+#             */
/*   Updated: 2024/10/22 10:45:54 by bikourar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_wd(char **spliting)
{
	int	i;

	i = 0;
	if (!spliting)
		return (0);
	while (spliting[i])
		i++;
	return (i);
}

int	strnlcpy(char **dst, unsigned int *j, char *src, char c)
{
	unsigned int	i;
	int				l;

	i = 0;
	l = 0;
	if (src[i] == c)
		(*dst)[*j] = src[i];
	src[i] = ' ';
	(addp((int *)j, 1), addp((int *)(&i), 1));
	while (src[i])
	{
		if (src[i] == c)
			break ;
		(*dst)[*j] = src[i];
		src[i] = ' ';
		(addp((int *)j, 1), addp((int *)(&i), 1));
	}
	if (src[i] == c)
		(*dst)[*j] = src[i];
	src[i] = ' ';
	(addp((int *)j, 1), addp((int *)(&i), 1));
	l = i;
	return (l);
}

t_sh	*lstlast_tsh(t_sh **lst)
{
	t_sh	*tmp;

	if (!lst)
		return (NULL);
	tmp = *lst;
	while (tmp != NULL)
	{
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

void	*cmt(t_sh *cm, int i)
{
	t_sh	*tp;
	t_redir	*dr;

	if (i == 1 && cm != NULL && *cm->args == NULL)
	{
		tp = cm;
		while (tp->next)
		{
			if (*tp->args != NULL)
				return (*tp->args);
			tp = tp->next;
		}
		return (*tp->args);
	}
	else if (i == 0 && cm != NULL)
	{
		tp = lstlast_tsh(&cm);
		dr = ltdr(&tp->dir);
		return (dr);
	}
	return (*cm->args);
}

t_redir	*ltdr(t_redir **lst)
{
	t_redir	*tmp;

	if (!lst)
		return (NULL);
	tmp = *lst;
	while (tmp != NULL)
	{
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}
