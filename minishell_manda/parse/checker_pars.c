/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_pars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bikourar <bikourar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:25:14 by bikourar          #+#    #+#             */
/*   Updated: 2024/10/25 16:54:08 by bikourar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_op1(t_p i)
{
	if (i == input || i == output)
		return (1);
	else if (i == append || i == heredoc)
		return (1);
	return (0);
}

int	check_te(t_e i)
{
	if (i == in || i == out)
		return (1);
	else if (i == app || i == her_doc)
		return (1);
	return (0);
}

int	check_dd(char *str, char c)
{
	int	i;

	i = 0;
	if (str[i] == c)
		i++;
	while (str[i])
	{
		if (str[i] == c)
			break ;
		i++;
	}
	if (str[i] == c)
		return (1);
	return (0);
}

int	check_redir_quote(char *str, int *i, int k)
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

void	check_counte(int *j, int flg)
{
	if (flg == 0)
		addp(j, 1);
	else if (flg > 0)
		addp(j, flg);
}
