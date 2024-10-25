/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bikourar <bikourar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 23:29:26 by bikourar          #+#    #+#             */
/*   Updated: 2024/10/25 16:54:08 by bikourar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_input(char *src, int *i, t_exp **lst)
{
	char	*dst;
	int		j;
	int		chmod;

	if (src[*i] && src[*i] == '$')
		*i += 1;
	j = 0;
	dst = (char *)ft_allocate(1, sizeof(char) * ((ft_strlen(src) + 1)));
	if (faile((*lst), dst, TRUE))
		return ;
	dst[j++] = '$';
	chmod = 0;
	while (src[*i])
	{
		if (!valid_expand(src[*i]))
			break ;
		if (is_nbr(src[*i]) && is_nbr(src[(*i - 1)]) && src[(*i - 2)] == '$')
			break ;
		dst[j++] = src[*i];
		*i += 1;
	}
	dst[j] = '\0';
	p_attr(&chmod, 4, 0, 0);
	(ad_bk_exp(lst, upgrade_input(dst, &chmod)));
}

void	copy_whit_sq(char *src, int *i, t_exp **lst)
{
	char	*dst;
	int		j;
	int		chmod;

	dst = (char *)ft_allocate(1, sizeof(char) * (ft_strlen(src) + 1));
	if (faile((*lst), dst, TRUE))
		return ;
	chmod = 0;
	j = 0;
	while (src[*i])
	{
		if (j != 0 && src[*i] == '\'')
			break ;
		dst[j++] = src[*i];
		*i += 1;
	}
	dst[j++] = '\'';
	dst[j] = '\0';
	(p_attr(&chmod, 0, 0, 0), ad_bk_exp(lst, upgrade_input(dst, &chmod)));
	if (src[*i] == '\'')
		*i += 1;
}

void	copy_whit_dq(char *src, int *i, t_exp **lst)
{
	char	*dst;
	int		j;
	int		chmod;

	dst = (char *)ft_allocate(1, sizeof(char) * (ft_strlen(src) + 1));
	if (faile((*lst), dst, TRUE))
		return ;
	chmod = 0;
	j = 0;
	while (src[*i])
	{
		if (j != 0 && src[*i] == '\"')
			break ;
		dst[j++] = src[*i];
		*i += 1;
	}
	dst[j++] = '\"';
	dst[j] = '\0';
	p_attr(&chmod, 4, 0, 0);
	(ad_bk_exp(lst, upgrade_input(dst, &chmod)));
	if (src[*i] == '\"')
		*i += 1;
}

void	copy_standard(char *src, int *i, t_exp **lst, BOOL b)
{
	char	*dst;
	int		mod;
	int		j;
	int		p;

	dst = (char *)ft_allocate(1, sizeof(char) * (ft_strlen(src) + 1));
	if (faile((*lst), dst, TRUE))
		return ;
	mod = 0;
	j = 0;
	p = *i;
	while (src[*i])
	{
		if (valid_condtion(src, *i) || (b && isquote(src[*i])))
			break ;
		else if (b && src[*i] == '$' && old(&src[p]) && isquote(src[(*i + 1)]))
			*i += 1;
		else if (w_sp(src[*i]) && b == TRUE)
			break ;
		dst[j++] = src[*i];
		*i += 1;
	}
	dst[j] = '\0';
	(p_attr(&mod, 0, 0, 0), ad_bk_exp(lst, upgrade_input(dst, &mod)));
}

t_exp	*update_input(char *in, t_exp **lst, BOOL b)
{
	t_exp	*head;
	int		i;

	i = 0;
	while (in[i])
	{
		if (valid_condtion(in, i))
			copy_input(in, &i, lst);
		else if (b == TRUE && e_s(in[i]) && e_s(in[i + 1]))
			copy_empty(in, &i, lst, FALSE);
		else if (in[i] == '$' && in[i + 1] == '?')
			copy_status(in, &i, lst);
		else if (in[i] == '\'' && b == TRUE)
			copy_whit_sq(in, &i, lst);
		else if (in[i] == '\"' && b == TRUE)
			copy_whit_dq(in, &i, lst);
		else if (w_sp(in[i]) && b == TRUE)
			skip_wspace(in, &i, lst);
		else
			copy_standard(in, &i, lst, b);
		if (faile((*lst), NULL, FALSE))
			return (NULL);
	}
	return (head = (*lst), head);
}
