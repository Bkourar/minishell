/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool2_process_reds.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bikourar <bikourar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 23:13:55 by bikourar          #+#    #+#             */
/*   Updated: 2024/10/24 23:29:20 by bikourar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_wqoute(char *arr, int *i, t_dir **lst)
{
	char	*dst;
	int		chmod;
	int		j;

	if (arr[*i] && arr[*i] == '$')
		*i += 1;
	dst = (char *)ft_allocate(1, sizeof(char) * ft_strlen(arr) + 1);
	if (failed(*lst, dst, TRUE))
		return ;
	chmod = 0;
	j = 0;
	while (arr[*i])
	{
		if (is_nbr(arr[(*i - 1)]) && is_nbr(arr[*i]))
			break ;
		if (!valid_expand(arr[*i]))
			break ;
		dst[j++] = arr[*i];
		*i += 1;
	}
	dst[j] = '\0';
	o_p(&chmod, 4, 2, 1);
	(add_dir(lst, up_redire(dst, &chmod, 0)));
}

void	copy_in_sqoute(char *src, int *i, t_dir **lst)
{
	char	*dst;
	int		chmod;
	int		j;

	dst = (char *)ft_allocate(1, sizeof(char) * ft_strlen(src) + 1);
	if (failed(*lst, dst, TRUE))
		return ;
	chmod = 0;
	j = 0;
	while (src[*i] && src[*i] != '\"')
	{
		if (j != 0 && (src[*i] == '\'' || src[*i] == '$'))
			break ;
		else
			dst[j++] = src[*i];
		*i += 1;
	}
	dst[j] = '\0';
	o_p(&chmod, 0, 2, 1);
	(add_dir(lst, up_redire(dst, &chmod, 0)));
}

void	copy_singleq(char *src, int *i, t_dir **lst)
{
	char	*dst;
	int		chmod;
	int		j;

	dst = (char *)ft_allocate(1, sizeof(char) * 2);
	if (failed(*lst, dst, TRUE))
		return ;
	chmod = 0;
	j = 0;
	if (src[*i] == '\'')
		dst[j++] = src[*i];
	dst[j] = '\0';
	o_p(&chmod, 0, 0, 1);
	(add_dir(lst, up_redire(dst, &chmod, 0)));
	*i += 1;
}

void	parsse_wesq(char *src, int *i, t_dir **lst)
{
	while (src[*i] && src[*i] != '\"')
	{
		if (src[*i] == '\'')
			copy_singleq(src, i, lst);
		else if (valid_condtion(src, *i))
			expand_wqoute(src, i, lst);
		else
			copy_in_sqoute(src, i, lst);
		if (failed(*lst, NULL, FALSE))
			return ;
	}
}

void	copy_std_norm(char *src, int *i, t_dir **lst)
{
	char	*dst;
	int		chmod;
	int		j;

	dst = (char *)ft_allocate(1, sizeof(char) * ft_strlen(src) + 1);
	if (failed(*lst, dst, TRUE))
		return ;
	chmod = 0;
	j = 0;
	while (src[*i] && src[*i] != '\"')
	{
		if (j != 0 && (src[*i] == '\'' || src[*i] == '$' || src[*i] == '\"'))
			break ;
		else
		{
			dst[j++] = src[*i];
			*i += 1;
		}
	}
	dst[j] = '\0';
	o_p(&chmod, 0, 2, 1);
	(add_dir(lst, up_redire(dst, &chmod, 0)));
}
