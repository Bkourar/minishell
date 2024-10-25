/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bikourar <bikourar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 23:13:21 by bikourar          #+#    #+#             */
/*   Updated: 2024/10/24 23:25:33 by bikourar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_condtion(char *str, int p)
{
	if (str[p] == '$' && valid_expand(str[p + 1]))
		return (1);
	return (0);
}

int	is_nbr(char c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	ambiguous_redirect(t_redir **hd)
{
	t_redir	*tp;

	tp = (*hd);
	while (tp)
	{
		if (tp->tp == ambiguos)
			return (1);
		else if (tp->tp == sig_hdc)
			return (2);
		tp = tp->next;
	}
	return (0);
}

int	valid_expand(char c)
{
	if (is_nbr(c) || c == '_' || is_alpha(c))
		return (1);
	return (0);
}

int	is_alpha(char c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}
