/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bikourar <bikourar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:25:52 by bikourar          #+#    #+#             */
/*   Updated: 2024/10/14 10:22:24 by bikourar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ck_and_dp(char c)
{
	char	*dst;
	char	c1[2];

	if (c == '\0')
		return (NULL);
	dst = NULL;
	if (c == '\'')
		c1[0] = '\'';
	else if (c == '\"')
		c1[0] = '\"';
	c1[1] = '\0';
	dst = ft_strdup(c1);
	if (!dst)
		return (write(2, "faile allocation\n", 18), NULL);
	return (dst);
}

char	*dup_quote(char *str, int *i, char c)
{
	char	*dst;
	int		j;

	dst = (char *)ft_allocate(1, sizeof(char) * (ft_strlen(str) + 1));
	if (!dst)
		return (write(2, "faile allocation\n", 18), NULL);
	if (str[*i] == c)
		*i += 1;
	j = 0;
	while (str[*i])
	{
		if (str[*i] == c)
		{
			break ;
		}
		dst[j++] = str[*i];
		*i += 1;
	}
	return (dst[j] = '\0', dst);
}

void	ft_lstadd_back_ttk(t_tk **lst, t_tk *new)
{
	t_tk	*temp;

	if (lst == NULL)
		return ;
	if (!(*lst))
	{
		(*lst) = new;
		new->pv = NULL;
		return ;
	}
	temp = *lst;
	while (temp->nx)
		temp = temp->nx;
	temp->nx = new;
	new->pv = temp;
}

t_tk	*ft_lstlast(t_tk **lst)
{
	t_tk	*tmp;

	if (!lst)
		return (NULL);
	tmp = *lst;
	while (tmp != NULL)
	{
		if (tmp->nx == NULL)
			break ;
		tmp = tmp->nx;
	}
	return (tmp);
}

t_tk	*ft_lstnew(char *content, BOOL b)
{
	t_tk	*n_node;

	n_node = (t_tk *)ft_allocate(1, sizeof(t_tk));
	if (!n_node)
		return (NULL);
	if (b == TRUE)
		n_node->checker = 0;
	n_node->token = ft_strdup(content);
	if (!n_node->token)
		return (NULL);
	n_node->nx = NULL;
	return (n_node);
}
