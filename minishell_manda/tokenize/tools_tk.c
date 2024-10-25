/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_tk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bikourar <bikourar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:24:36 by bikourar          #+#    #+#             */
/*   Updated: 2024/10/25 16:54:08 by bikourar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	rpl_str_quote(char *dst, int *i, char *str, char c)
{
	int	j;

	j = 0;
	while (str[j])
	{
		if (j != 0 && str[j] == c)
		{
			j++;
			break ;
		}
		dst[*i] = ' ';
		*i += 1;
		j++;
	}
	if (str[j - 1] == c)
	{
		dst[*i] = ' ';
		*i += 1;
	}
	return (j);
}

int	replace_space(char *dst, int *i, char *src)
{
	int	j;

	j = 0;
	while (src[j] && (w_sp(src[j]) || check_dir(src[j])))
		j++;
	if ((src[j] == '\'' || src[j] == '\"'))
		return (rpl_str_quote(dst, i, &src[j], src[j]) + j);
	while (src[j])
	{
		if (w_sp(src[j]) || check_dir(src[j]))
			break ;
		dst[*i] = ' ';
		j++;
		*i += 1;
	}
	return (j);
}

char	*restory_cmd(char *src)
{
	char	*stock;
	int		i;
	int		j;

	i = 0;
	j = 0;
	stock = NULL;
	while (src[i])
	{
		if (src[i] == '|' && !check_pipe(src, i, 0))
		{
			i++;
			stock = ft_allocate(1, sizeof(char) * (ft_strlen(&src[i]) + 1));
			if (!stock)
				return (NULL);
			while (src[i])
				stock[j++] = src[i++];
			stock[j] = '\0';
			break ;
		}
		i++;
	}
	return (stock);
}

void	copy_empty(char *s, int *i, t_exp **l, BOOL b)
{
	char	*dst;
	int		mod;

	mod = 0;
	if (b == TRUE && s[*i] == (char)-15708 && s[(*i + 1)] == '\0')
		addp(i, 1);
	else if (!b && s[*i] == (char)-15708 && s[(*i + 1)] == (char)-15708)
		addp(i, 2);
	dst = ft_strdup("¤");
	if (faile((*l), dst, TRUE))
		return ;
	(p_attr(&mod, 0, 0, 0), ad_bk_exp(l, upgrade_input(dst, &mod)));
}
