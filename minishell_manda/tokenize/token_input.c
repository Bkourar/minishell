/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bikourar <bikourar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:23:42 by bikourar          #+#    #+#             */
/*   Updated: 2024/10/25 16:54:08 by bikourar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	copy_quote(char *in, int *i, t_tk **l, char c)
{
	char	*dst;
	int		j;

	dst = ck_and_dp(in[*i]);
	if (failing((*l), dst, TRUE))
		return ;
	(ft_lstadd_back_ttk(l, ft_lstnew(dst, TRUE)), addp(i, 1));
	dst = (char *)ft_allocate(1, sizeof(char) * (ft_strlen(in) + 1));
	if (in[*i] == '\0' || failing((*l), dst, TRUE))
		return ;
	j = 0;
	while (in[*i])
	{
		if (in[*i] == c)
			break ;
		dst[j++] = in[*i];
		*i += 1;
	}
	if (in[(*i - 1)] != c)
		(dst[j] = '\0') && (ft_lstadd_back_ttk(l, ft_lstnew(dst, TRUE)), TRUE);
	dst = ck_and_dp(in[*i]);
	if (in[*i] == '\0' || failing((*l), dst, TRUE))
		return ;
	(ft_lstadd_back_ttk(l, ft_lstnew(dst, TRUE)), addp(i, 1));
}

static void	copy_dir(char *in, int *i, t_tk **l)
{
	char	*dst;

	dst = NULL;
	if (in[*i] == '<' && in[(*i + 1)] == '<')
		(dst = ft_strdup("<<")) && (addp(i, 2), TRUE);
	else if (in[*i] == '>' && in[(*i + 1)] == '>')
		(dst = ft_strdup(">>")) && (addp(i, 2), TRUE);
	else if (in[*i] == '<' && in[(*i + 1)] != '<')
		(dst = ft_strdup("<")) && (addp(i, 1), TRUE);
	else if (in[*i] == '>' && in[(*i + 1)] != '>')
		(dst = ft_strdup(">")) && (addp(i, 1), TRUE);
	if (failing((*l), dst, TRUE))
		return ;
	ft_lstadd_back_ttk(l, ft_lstnew(dst, TRUE));
}

static void	copy_pd(char *in, int *i, t_tk **l)
{
	char	*dst;

	dst = NULL;
	if (in[*i] == '$')
		dst = ft_strdup("$");
	else if (in[*i] == '|')
		dst = ft_strdup("|");
	*i += 1;
	if (failing((*l), dst, TRUE))
		return ;
	ft_lstadd_back_ttk(l, ft_lstnew(dst, TRUE));
}

static void	copy_stdin(char *in, int *i, t_tk **l)
{
	char	*dst;
	int		j;

	dst = (char *)ft_allocate(1, sizeof(char) * (ft_strlen(in) + 1));
	if (failing((*l), dst, TRUE))
		return ;
	j = 0;
	while (in[*i])
	{
		if (!check_op(in[*i]) || w_sp(in[*i]))
			break ;
		dst[j++] = in[*i];
		*i += 1;
	}
	dst[j] = '\0';
	ft_lstadd_back_ttk(l, ft_lstnew(dst, TRUE));
}

char	**token_input(char *in, t_tk **lst)
{
	int		i;

	i = 0;
	while (in[i] != '\0')
	{
		if (isquote(in[i]))
			copy_quote(in, &i, lst, in[i]);
		else if (check_dir(in[i]))
			copy_dir(in, &i, lst);
		else if (check_pd(in[i]))
			copy_pd(in, &i, lst);
		else if (w_sp(in[i]))
			i++;
		else
			copy_stdin(in, &i, lst);
		if (failing((*lst), NULL, FALSE))
			return (NULL);
	}
	return (double_arr(lst));
}
