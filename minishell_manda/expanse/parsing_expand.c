/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bikourar <bikourar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 23:13:36 by bikourar          #+#    #+#             */
/*   Updated: 2024/10/25 17:46:57 by bikourar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_in_sq(char *src, int *i, t_exp **lst)
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
		if (j != 0 && (src[*i] == '\'' || src[*i] == '$'))
			break ;
		else
			dst[j++] = src[*i];
		*i += 1;
	}
	dst[j] = '\0';
	p_attr(&chmod, 0, 0, 1);
	(ad_bk_exp(lst, upgrade_input(dst, &chmod)));
}

BOOL	check_bfaf_wsp(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (!w_sp(str[i]) && i)
			break ;
		else if (w_sp(str[i]))
			j++;
		i++;
	}
	if (i != 0 && j == i)
		return (TRUE);
	return (FALSE);
}

char	**parse_value(t_exp **hd, t_env **env, BOOL *b)
{
	char	**spl;
	t_env	*tp;

	tp = (*env);
	while (tp)
	{
		if (!ft_strcmp((*hd)->input, tp->var))
		{
			if (condition_for_split(&(*hd)))
				return (spl[0] = give_arg(env, (*hd), &spl), spl[1] = 0, spl);
			*b = check_bfaf_wsp(tp->value);
			spl = ft_split(tp->value, ' ');
			if (!spl)
				return (write(2, "faile allocation\n", 18), NULL);
			return (spl);
		}
		tp = tp->next;
	}
	spl = (char **)ft_allocate(1, (1 + 1) * sizeof(char *));
	if (!spl)
		return (write(2, "faile allocation\n", 18), NULL);
	spl[0] = ft_strdup("ß");
	if (!spl[0])
		return (write(2, "faile allocation\n", 18), NULL);
	return (spl[1] = 0, spl);
}

void	autortion(char **s, t_exp **l, int rwx, BOOL *b)
{
	static int	k;
	int			i;
	int			j;

	i = 0;
	j = 2;
	while (s && s[i] && *b == TRUE)
	{
		if (j % 2 != 0)
			(ad_bk_exp(l, upgrade_input(s[i], &rwx)), addp(&i, 1));
		else
			ad_bk_exp(l, upgrade_input(" ", &k));
		j++;
	}
	i = 0;
	j = 2;
	while (s && s[i] && *b == FALSE)
	{
		if (j % 2 == 0)
			(ad_bk_exp(l, upgrade_input(s[i], &rwx)), addp(&i, 1));
		else
			ad_bk_exp(l, upgrade_input(" ", &k));
		j++;
	}
}

char	*give_arg(t_env **env, t_exp *l, char ***in)
{
	t_env	*tp;

	(*in) = (char **)ft_allocate(1, (1 + 1) * sizeof(char *));
	if (!(*in))
		return (write(2, "faile allocation\n", 18), NULL);
	tp = (*env);
	while (tp)
	{
		if (!ft_strcmp(l->input, tp->var))
			break ;
		tp = tp->next;
	}
	return (ft_strdup(tp->value));
}
