/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processe_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bikourar <bikourar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:25:39 by bikourar          #+#    #+#             */
/*   Updated: 2024/10/13 16:25:40 by bikourar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_er_1(t_tk **f, t_tk **l)
{
	t_tk	*t;

	if ((*f)->type == Pipe || (!(*f)->nx && check_op1((*f)->type)))
		return (synatx_error((*f)->token), 1);
	else if ((*l)->type == Pipe)
		return (synatx_error((*l)->token), 1);
	else if (check_op1((*l)->type) && !check_op1((*l)->pv->type))
		return (print_errors(), 1);
	t = (*f);
	while (t->nx != NULL)
	{
		if (t->type == Pipe && t->nx->type == Pipe)
			return (synatx_error("|"), 1);
		t = t->nx;
	}
	return (0);
}

int	process_er_2(t_tk **f)
{
	t_tk	*tp;
	t_tk	*tp1;

	tp = (*f);
	tp1 = (*f)->nx;
	while (tp1 != NULL)
	{
		if (check_op1(tp->type) && check_op1(tp1->type))
			return (synatx_error(tp1->token), 1);
		else if (check_op1(tp->type) && tp1->type == Pipe)
			return (synatx_error(tp1->token), 1);
		tp = tp1;
		tp1 = tp1->nx;
	}
	return (0);
}

int	process_er_4(t_tk **l)
{
	t_tk	*f;
	char	c;
	int		i;

	f = (*l);
	i = 0;
	while (f)
	{
		if (f != NULL && f->type == s_quot)
			c = loop(&f, f->type, &i);
		else if (f != NULL && f->type == d_quot)
			c = loop(&f, f->type, &i);
		if (!(i == 2 || i == 0) && f == NULL)
			return (synatx_quotes(c), 1);
		else if (i == 2 && f != NULL)
			i = 0;
		else if (i == 0 && f != NULL)
		{
			i = 0;
			f = f->nx;
		}
	}
	return (0);
}

int	process_er_5(t_tk **lst)
{
	t_tk	*tmp;

	tmp = (*lst);
	while (tmp != NULL)
	{
		if (!ft_strcmp(tmp->token, "echo"))
		{
			tmp = tmp->nx;
			if (tmp == NULL)
				break ;
			else if (tmp->type == s_quot || tmp->type == d_quot)
			{
				if (process_er_4(&tmp) == 1)
					return (1);
			}
		}
		tmp = tmp->nx;
	}
	return (0);
}

int	process_er_3(char c0, char c1)
{
	if (c1 == '>')
		return (synatx_error(">"), 1);
	else if (c1 == '<')
		return (synatx_error("<"), 1);
	else if (c0 == '|' && c1 == '>')
		return (synatx_error(">"), 1);
	else if (c0 == '|' && c1 == '<')
		return (synatx_error("<"), 1);
	else if (c1 == '|')
		return (synatx_error("|"), 1);
	return (0);
}
