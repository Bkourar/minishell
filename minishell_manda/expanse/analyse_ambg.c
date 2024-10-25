/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse_ambg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bikourar <bikourar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 23:12:58 by bikourar          #+#    #+#             */
/*   Updated: 2024/10/25 16:54:08 by bikourar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change(t_redir **hd, BOOL b)
{
	if (b == FALSE)
	{
		(*hd)->fd_her = -1;
		(*hd)->file_name = NULL;
		(*hd)->tp = ambiguos;
	}
	else
	{
		(*hd)->fd_her = 1;
		(*hd)->tp = sig_hdc;
	}
}

int	check_error_ambiguous(t_dir *nd, t_dir **head)
{
	int	i;

	if (nd == NULL)
		return (0);
	i = lstsiz_dr((*head));
	if (nd->ambg == AMBG_5)
		return (1);
	else if (nd->ambg == AMBG_1 && i == 1)
		return (1);
	else if (nd->ambg == AMBG_2 && (nd->prv && nd->prv->par->wd == wrd))
		return (1);
	else if (nd->ambg == AMBG_3 && (nd->next && nd->next->par->wd == wrd))
		return (1);
	else if (nd->ambg == AMBG_4 && i > 1)
		return (1);
	return (0);
}

static int	sort_case_ambg(char *in)
{
	int	j;
	int	i;

	if (in[0] == '\0')
		return (1);
	i = count_word(in, ' ');
	j = ft_strlen(in);
	if (i > 1)
		return (5);
	else if (w_sp(in[0]) && w_sp(in[j - 1]))
		return (4);
	else if (w_sp(in[0]) && !w_sp(in[j - 1]))
		return (2);
	else if (w_sp(in[j - 1]) && !w_sp(in[0]))
		return (3);
	return (6);
}

t_dir	*analyse_case_ambg(t_dir *tp, t_env **ev)
{
	char	*in;
	t_dir	*lst;

	lst = NULL;
	while (tp != NULL)
	{
		if (tp->par->st == not_join && tp->par->tp == exp)
		{
			in = search_in_eva(tp, ev);
			(add_dir(&lst, config_redirect(in, sort_case_ambg(in), tp)));
		}
		else if (tp->par->st == join && tp->par->tp == exp)
		{
			in = search_in_eva(tp, ev);
			(add_dir(&lst, config_redirect(in, 0, tp)));
		}
		else
			add_dir(&lst, config_redirect(tp->input, 0, tp));
		tp = tp->next;
	}
	return (lst);
}

t_dir	*check_ambiguous_redirect(t_dir **l, char *in, t_redir **d)
{
	t_dir	*tp;

	if ((*l) == NULL)
		return (NULL);
	tp = (*l);
	while (tp)
	{
		if (tp->ambg == 0)
			tp = tp->next;
		else
		{
			if (check_error_ambiguous(tp, l) != 0)
				return (put_ambeg(in), change(d, FALSE), tp);
			else
				tp = tp->next;
		}
	}
	return (tp = (*l), tp);
}
