/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_exp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bikourar <bikourar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 23:13:28 by bikourar          #+#    #+#             */
/*   Updated: 2024/10/24 23:27:44 by bikourar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	faile(t_exp *l, void *arg, BOOL flg)
{
	if (l && (l->prv != NULL && l->prv->ck != 1)
		&& (flg == TRUE && arg == NULL))
	{
		l->prv->ck = 1;
		write(2, "faile allocation\n", 18);
		write(2, "faile 1\n", 9);
		return (1);
	}
	else if (l && l->prv != NULL && l->prv->ck == 1)
		return (puts("here"), 1);
	else if (l != NULL && l->ck == 1)
		return (puts("here"), 1);
	else if (arg == NULL && flg == TRUE)
	{
		if (l != NULL)
			l->ck = 1;
		write(2, "faile allocation\n", 18);
		write(2, "faile 2\n", 9);
		return (1);
	}
	return (0);
}

int	check_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
	}
	if (i != 0 && valid_expand(str[i - 1])
		&& valid_expand(str[i + 1]))
		return (1);
	return (0);
}

int	condition_for_split(t_exp **hd)
{
	t_exp	*tp;

	if ((*hd) != NULL || (*hd)->prv != NULL || (*hd)->next != NULL)
		return (0);
	tp = (*hd);
	if (tp->prv->input[0] == '=' && tp->next->input[0] == '=')
		return (0);
	else if (tp->prv->input[0] == '=' && tp->prv->set->tp == not_exp)
		return (0);
	else if (tp->next->input[0] == '=' && tp->next->set->tp == not_exp)
		return (0);
	else if (check_equal(tp->input))
		return (0);
	return (1);
}

int	valid_join(t_exp *nd)
{
	if (nd == NULL || nd->input[0] == (char)-62)
		return (0);
	if (nd->set->st == join)
		return (1);
	else if (ft_strcmp(nd->input, " ") != 0
		&& (nd->prv != NULL && nd->prv->set->st == join))
		return (1);
	else if (ft_strcmp(nd->input, " ") != 0
		&& (nd->next != NULL && nd->next->set->st == join))
		return (1);
	else if (ft_strcmp(nd->input, " ") != 0
		&& (nd->prv != NULL && ft_strcmp(nd->prv->input, " ") != 0))
		return (1);
	else if (ft_strcmp(nd->input, " ") != 0
		&& (nd->next != NULL && ft_strcmp(nd->next->input, " ") != 0))
		return (1);
	return (0);
}
