/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bikourar <bikourar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:29:25 by bikourar          #+#    #+#             */
/*   Updated: 2024/10/25 16:54:08 by bikourar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_op(char c)
{
	if (!(c == '<' || c == '>' || c == '$'
			|| c == '|' || c == '\"' || c == '\''))
		return (1);
	return (0);
}

int	check_dir(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

int	check_redir(char const *str)
{
	if (!ft_strcmp(str, "<<") || !ft_strcmp(str, ">>"))
		return (1);
	return (0);
}

int	isquote(char c)
{
	if (c == '\"' || c == '\'')
		return (1);
	return (0);
}

int	w_sp(char c)
{
	if (c == ' ' || c == '\t' || c == '\v')
		return (1);
	else if (c == '\r' || c == '\f')
		return (1);
	return (0);
}
