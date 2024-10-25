/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bikourar <bikourar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:25:05 by bikourar          #+#    #+#             */
/*   Updated: 2024/10/13 16:25:07 by bikourar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tk	*pi_processing_cmd(t_tk **lst)
{
	t_tk	*tmp;
	char	c1;
	char	c2;
	int		j;

	tmp = (*lst);
	j = 0;
	while (tmp != NULL && j != 1)
	{
		c1 = tmp->token[0];
		c2 = tmp->token[1];
		if (tmp->type == err)
			j = process_er_3(c1, c2);
		tmp = tmp->nx;
	}
	tmp = ft_lstlast(lst);
	if (j == 0 && tmp->type == L_err)
		return (synatx_error(tmp->token), NULL);
	else if (j == 1 || process_er_1(lst, &tmp) || process_er_2(lst))
		return (NULL);
	else if (process_er_4(lst) || process_er_5(lst))
		return (NULL);
	return ((*lst));
}

char	loop(t_tk **tmp, t_p type, int *j)
{
	char	c;

	while ((*tmp) != NULL && *j != 2)
	{
		if ((*tmp)->type == type)
		{
			c = (*tmp)->token[0];
			*j += 1;
		}
		(*tmp) = (*tmp)->nx;
	}
	return (c);
}
