/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_tk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bikourar <bikourar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:22:39 by bikourar          #+#    #+#             */
/*   Updated: 2024/10/25 16:54:08 by bikourar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	chechecker_pipe(char *str, int j, int i)
{
	int		addp;
	char	c;

	addp = 0;
	while (str[i])
	{
		if (isquote(str[i]) && addp == 0)
		{
			c = str[i];
			addp++;
			i++;
			while (str[i] && str[i] != c)
			{
				if (i == j)
					return (1);
				i++;
			}
			if (str[i] && str[i] == c)
				addp++;
		}
		if (addp == 2)
			addp = 0;
		i++;
	}
	return (0);
}

int	chechecker_redir_quote(char *str, int *i, int k)
{
	k = *i;
	while (str[k])
	{
		if (check_dir(str[k]))
		{
			if (w_sp(str[(k + 1)]))
			{
				k += 1;
				while (str[k] && w_sp(str[k]))
					k++;
				if (isquote(str[k]))
					return (*i += k, 1);
				else
					break ;
			}
			else if (isquote(str[k + 1]))
				return (*i += 1, 1);
			else
				break ;
		}
		else
			break ;
	}
	return (0);
}

int	check_pd(char c)
{
	if (c == '|' || c == '$')
		return (1);
	return (0);
}

int	failing(t_tk *l, void *arg, BOOL flg)
{
	if (l == NULL)
		return (0);
	if ((l->pv && l->pv->checker != 1) && (flg && !arg))
	{
		l->pv->checker = 1;
		write(2, "faile allocation\n", 18);
		write(2, "faile 1\n", 9);
		return (1);
	}
	else if (l->pv != NULL && l->pv->checker == 1)
		return (1);
	else if (l != NULL && l->checker == 1)
		return (1);
	else if (arg == NULL && flg == TRUE)
	{
		if (l != NULL)
			l->checker = 1;
		write(2, "faile allocation\n", 18);
		write(2, "faile 2\n", 9);
		return (1);
	}
	return (0);
}

void	check_in_quote(char *inf, char c, int *i)
{
	if (inf[*i] == c)
		*i += 1;
	while (inf[*i])
	{
		if (inf[*i] == c)
			break ;
		*i += 1;
	}
	*i += 1;
}
