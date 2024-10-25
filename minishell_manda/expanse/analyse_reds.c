/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse_reds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bikourar <bikourar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 23:13:09 by bikourar          #+#    #+#             */
/*   Updated: 2024/10/25 16:54:08 by bikourar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*concatition_dir(t_dir **lst)
{
	t_dir	*nd1;
	char	*str;

	str = NULL;
	if ((*lst) == NULL)
		return (str);
	nd1 = (*lst);
	while (nd1)
	{
		str = ft_strjoin(str, nd1->input);
		if (!str)
			return (write(2, "faile allocation\n", 18), NULL);
		nd1 = nd1->next;
	}
	return (str);
}

int	check_empty(char *s)
{
	if (s == NULL)
		return (0);
	if (s[0] == 34 && s[1] == 34 && s[2] == '\0')
		return (1);
	else if (s[0] == 39 && s[1] == 39 && s[2] == '\0')
		return (1);
	if (s[0] == 34 && s[1] == 34 && (w_sp(s[2]) || check_dir(s[2])))
		return (1);
	else if (s[0] == 39 && s[1] == 39 && (w_sp(s[2]) || check_dir(s[2])))
		return (1);
	return (0);
}

char	*process_dr(char *in, t_env **env, t_redir *d, int *i)
{
	t_dir	*head;
	char	*correct;

	head = NULL;
	if (d != NULL && d->tp == her_doc)
		return (ft_strdup(&in[*i]));
	if (check_empty(&in[*i]))
		return (ft_strdup("Œ"));
	head = analyse_input(in, &head, i);
	if (!head)
		return (NULL);
	head = upgrade_list(mise_ajour_input(&head), &head);
	if (!head)
		return (NULL);
	head = analyse_case_ambg(head, env);
	head = check_ambiguous_redirect(&head, &in[*i], &d);
	if (head == NULL)
		return (NULL);
	correct = concatition_dir(&head);
	if (!correct)
		return (NULL);
	return (correct);
}

void	give_status(char *arr, int *i, t_exp **lst, BOOL b)
{
	char	*dst;
	int		chmod;

	dst = NULL;
	chmod = 0;
	if (b == TRUE && !ft_strcmp(arr, "$?"))
	{
		dst = ft_itoa(ft_hrb(0, 0));
		(p_attr(&chmod, 0, 0, 0));
	}
	else if (b == FALSE && arr[*i] == '$' && arr[(*i + 1)] == '?')
	{
		dst = ft_itoa(ft_hrb(0, 0));
		(p_attr(&chmod, 0, 2, 1));
	}
	if (faile((*lst), dst, TRUE))
		return ;
	*i += 2;
	(ad_bk_exp(lst, upgrade_input(dst, &chmod)));
}
