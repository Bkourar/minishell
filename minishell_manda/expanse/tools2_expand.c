/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bikourar <bikourar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 23:32:47 by bikourar          #+#    #+#             */
/*   Updated: 2024/10/24 23:32:48 by bikourar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand(char *arr, int *i, t_exp **lst)
{
	char	*dst;
	int		chmod;
	int		j;

	if (arr[*i] && arr[*i] == '$')
		*i += 1;
	dst = (char *)ft_allocate(1, sizeof(char) * ft_strlen(arr) + 1);
	if (faile((*lst), dst, TRUE))
		return ;
	chmod = 0;
	j = 0;
	while (arr[*i])
	{
		dst[j++] = arr[*i];
		*i += 1;
	}
	dst[j] = '\0';
	p_attr(&chmod, 4, 0, 0);
	(ad_bk_exp(lst, upgrade_input(dst, &chmod)));
}

void	expand_sq(char *arr, int *i, t_exp **lst)
{
	char	*dst;
	int		chmod;
	int		j;

	if (arr[*i] && arr[*i] == '$')
		*i += 1;
	dst = (char *)ft_allocate(1, sizeof(char) * ft_strlen(arr) + 1);
	if (faile((*lst), dst, TRUE))
		return ;
	chmod = 0;
	j = 0;
	while (arr[*i])
	{
		if (!valid_expand(arr[*i]))
			break ;
		if (is_nbr(arr[*i]) && is_nbr(arr[(*i - 1)]) && arr[(*i - 2)] == '$')
			break ;
		dst[j++] = arr[*i];
		*i += 1;
	}
	dst[j] = '\0';
	p_attr(&chmod, 4, 0, 1);
	(ad_bk_exp(lst, upgrade_input(dst, &chmod)));
}

void	parsse_sq(char *src, int *i, t_exp **lst)
{
	while (src[*i] && src[*i] != '\"')
	{
		if (src[*i] == '\'')
			copy_single_q(src, i, lst);
		else if (valid_condtion(src, *i))
			expand_sq(src, i, lst);
		else
			copy_in_sq(src, i, lst);
		if (faile((*lst), NULL, FALSE))
			return ;
	}
}

void	copy_std(char *src, int *i, t_exp **lst)
{
	char	*dst;
	int		chmod;
	int		j;

	dst = (char *)ft_allocate(1, sizeof(char) * ft_strlen(src) + 1);
	if (faile((*lst), dst, TRUE))
		return ;
	chmod = 0;
	j = 0;
	while (src[*i] && src[*i] != '\"')
	{
		if (j != 0 && (isquote(src[*i]) || src[*i] == '$'))
			break ;
		else
		{
			dst[j++] = src[*i];
			*i += 1;
		}
	}
	dst[j] = '\0';
	p_attr(&chmod, 0, 0, 1);
	(ad_bk_exp(lst, upgrade_input(dst, &chmod)));
}

void	copy_single_q(char *src, int *i, t_exp **lst)
{
	char	*dst;
	int		chmod;
	int		j;

	dst = (char *)ft_allocate(1, sizeof(char) * 2);
	if (faile((*lst), dst, TRUE))
		return ;
	chmod = 0;
	j = 0;
	if (src[*i] == '\'')
		dst[j++] = src[*i];
	dst[j] = '\0';
	p_attr(&chmod, 0, 0, 1);
	(ad_bk_exp(lst, upgrade_input(dst, &chmod)));
	*i += 1;
}
