/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bikourar <bikourar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 23:24:54 by bikourar          #+#    #+#             */
/*   Updated: 2024/10/24 23:24:55 by bikourar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_general(char *src, int *i, t_exp **lst)
{
	char	*dst;
	int		chmod;
	int		j;

	dst = (char *)ft_allocate(1, sizeof(char) * ft_strlen(src) + 1);
	if (faile((*lst), dst, TRUE))
		return ;
	chmod = 0;
	j = 0;
	while (src[*i])
	{
		dst[j++] = src[*i];
		*i += 1;
	}
	dst[j] = '\0';
	p_attr(&chmod, 0, 0, 0);
	(ad_bk_exp(lst, upgrade_input(dst, &chmod)));
}

void	cin_singl_q(char *src, int *i, t_exp **lst)
{
	char	*dst;
	int		chmod;
	int		j;

	if (src[*i] && src[*i] == '\'')
		*i += 1;
	dst = (char *)ft_allocate(1, sizeof(char) * ft_strlen(src) + 1);
	if (faile((*lst), dst, TRUE))
		return ;
	chmod = 0;
	j = 0;
	while (src[*i])
	{
		if (j != 0 && src[*i] == '\'')
			break ;
		else if (src[*i] == '\'' && j == 0)
			break ;
		dst[j++] = src[*i];
		*i += 1;
	}
	dst[j] = '\0';
	(p_attr(&chmod, 0, 0, 1), ad_bk_exp(lst, upgrade_input(dst, &chmod)));
	if (src[*i] && src[*i] == '\'')
		*i += 1;
}

void	parssing_expand(char *src, int *i, t_exp **head)
{
	if (src[*i] && src[*i] == '\"')
		*i += 1;
	while (src[*i] && src[*i] != '\"')
	{
		if (valid_condtion(src, *i))
			expand_sq(src, i, head);
		else if (src[*i] == '$' && src[(*i + 1)] == '?')
			give_status(src, i, head, FALSE);
		else if (src[*i] == '\'')
			parsse_sq(src, i, head);
		else
			copy_std(src, i, head);
		if (faile((*head), NULL, FALSE))
			return ;
	}
	if (src[*i] && src[*i] == '\"')
		i += 1;
}

t_exp	*update_list(char **in, t_exp **lst, BOOL b, int j)
{
	t_exp	*head;
	int		i;

	i = 0;
	head = NULL;
	while (in[i])
	{
		j = 0;
		if (in[i][0] == '$' && in[i][1] == '?' && in[i][2] == '\0')
			give_status(in[i], &j, &head, TRUE);
		else if (e_s(in[i][0]))
			copy_empty(in[i], &j, lst, TRUE);
		else if (in[i][0] == '$' && valid_expand(in[i][1]))
			expand(in[i], &j, &head);
		else if (b == TRUE && in[i][0] == '\"')
			parssing_expand(in[i], &j, &head);
		else if (b == TRUE && in[i][0] == '\'')
			cin_singl_q(in[i], &j, &head);
		else
			copy_general(in[i], &j, &head);
		if (faile((*lst), NULL, FALSE))
			return (NULL);
		i++;
	}
	return (head);
}
