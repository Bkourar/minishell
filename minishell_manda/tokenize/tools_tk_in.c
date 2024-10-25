/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_tk_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bikourar <bikourar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:24:47 by bikourar          #+#    #+#             */
/*   Updated: 2024/10/25 16:54:08 by bikourar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**double_arr(t_tk **l)
{
	t_tk	*tp;
	char	**s;
	int		i;

	s = (char **)ft_allocate(1, (ft_lstsize_tk((*l)) + 1) * sizeof(char *));
	if (!s)
		return (write(2, "faile allocation\n", 18), NULL);
	tp = (*l);
	i = 0;
	while (tp)
	{
		s[i++] = ft_strdup(tp->token);
		if (!s[i - 1])
			return (write(2, "faile allocation\n", 18), NULL);
		tp = tp->nx;
	}
	s[i] = 0;
	return (s);
}

int	check_pipe(char *str, int j, int i)
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

int	skp_w_sp(char *in)
{
	int	i;

	i = 0;
	while (in[i] && w_sp(in[i]))
		i++;
	return (i);
}

int	ft_lstsize_tk(t_tk *lst)
{
	int		i;
	t_tk	*node;

	node = lst;
	i = 0;
	while (node != NULL)
	{
		i++;
		node = node->nx;
	}
	return (i);
}

void	change_and_rpl(char *str, char *stack, int i)
{
	int	j;

	j = 0;
	while (str[i])
	{
		if (check_redir_quote(str, &i, 0))
			i += replace_space(stack, &j, &str[i]);
		else if (i != 0 && str[i] == ' ' && check_dir(str[i - 1]))
			i += replace_space(stack, &j, &str[i]);
		else if (i != 0 && !check_dir(str[i]) && check_dir(str[i - 1]))
			i += replace_space(stack, &j, &str[i]);
		else if (check_dir(str[i]) || w_sp(str[i]))
		{
			stack[j++] = ' ';
			i++;
		}
		else if (isquote(str[i]) && check_dd(&str[i], str[i]))
			i += strnlcpy(&stack, (unsigned int *)(&j), &str[i], str[i]);
		else
			stack[j++] = str[i++];
	}
	stack[j] = '\0';
}
