/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexic_wrd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bikourar <bikourar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:25:34 by bikourar          #+#    #+#             */
/*   Updated: 2024/10/22 10:45:54 by bikourar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	addp(int *addp, int val)
{
	*addp = *addp + val;
}

static void	up_date(char *str, t_tk **lst)
{
	t_tk	*node;

	if (!str)
	{
		if ((*lst) && (*lst)->pv != NULL)
			(*lst)->pv->checker = 1;
		return ;
	}
	(node = ft_lstnew(str, FALSE)) && (node->stat = ft_strdup("general"));
	if (!node || !node->token || !node->stat)
	{
		if ((*lst)->pv != NULL)
			(*lst)->pv->checker = 1;
		return ;
	}
	node->checker = 0;
	node->type = word;
	ft_lstadd_back_ttk(lst, node);
}

int	pars_word(char *input, t_tk **lst)
{
	if (!input)
	{
		if ((*lst) && (*lst)->pv != NULL)
			(*lst)->pv->checker = 1;
		return (1);
	}
	up_date(input, lst);
	return (0);
}

void	nxt(t_sh **tp)
{
	(*tp) = (*tp)->next;
}

void	ln(BOOL *bo, BOOL val)
{
	*bo = val;
}
