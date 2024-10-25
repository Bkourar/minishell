/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bikourar <bikourar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 23:27:56 by bikourar          #+#    #+#             */
/*   Updated: 2024/10/25 17:48:21 by bikourar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exp	*ifconfigration(t_exp **l, t_env **ev, BOOL *b)
{
	t_exp	*head;
	char	**s;
	int		wx;

	head = NULL;
	while ((*l))
	{
		if ((*l)->set->tp == exp && (*l)->set->st == not_join)
		{
			s = parse_value(&(*l), ev, b);
			autortion(s, &head, own_exp(4, (*l)->set->sp, 0), b);
		}
		else if ((*l)->set->tp == exp && (*l)->set->st == join)
		{
			wx = own_exp(4, (*l)->set->sp, 1);
			ad_bk_exp(&head, upgrade_input(s_and_r(&(*l), ev), &wx));
		}
		else
		{
			wx = own_exp((*l)->set->tp, (*l)->set->sp, (*l)->set->st);
			ad_bk_exp(&head, upgrade_input((*l)->input, &wx));
		}
		(*l) = (*l)->next;
	}
	return ((*l) = head, (*l));
}

static t_exp	*concatition(t_exp *n)
{
	t_exp	*head;
	char	*str;

	head = NULL;
	while (n)
	{
		str = NULL;
		if (valid_join(n))
		{
			while (n && valid_join(n))
			{
				str = ft_strjoin(str, n->input);
				if (!str)
					return (write(2, "faile allocation\n", 18), NULL);
				n = n->next;
			}
			ad_bk_exp(&head, config(str));
		}
		else
		{
			ad_bk_exp(&head, config(n->input));
			n = n->next;
		}
	}
	return (head);
}

static char	**result_expand(t_exp *hd, int i)
{
	char	**s;

	s = (char **)ft_allocate(1, (lstsiz_exp(hd) + 1) * sizeof(char *));
	if (!s)
		return (write(2, "faile allocation\n", 18), NULL);
	i = 0;
	while (hd)
	{
		if (!ft_strcmp(hd->input, " ") || !ft_strcmp(hd->input, "ß"))
			hd = hd->next;
		else
		{
			s[i++] = ft_strdup(hd->input);
			if (!s[i - 1])
				return (write(2, "faile allocation\n", 18), NULL);
			hd = hd->next;
		}
	}
	return (s[i] = 0, s);
}

char	**pi_processing_expand(char *str, t_env **env, BOOL b)
{
	char	**spl;
	t_exp	*head;
	BOOL	l;

	head = NULL;
	l = FALSE;
	if (str == NULL)
		return (NULL);
	head = update_input(str, &head, b);
	if (!head)
		return (NULL);
	spl = update_array(&head, 0);
	if (spl == NULL)
		return (NULL);
	head = update_list(spl, &head, b, 0);
	if (!head)
		return (NULL);
	head = ifconfigration(&head, env, &l);
	if (!head)
		return (NULL);
	head = concatition(head);
	if (!head)
		return (NULL);
	return (result_expand(head, 0));
}
