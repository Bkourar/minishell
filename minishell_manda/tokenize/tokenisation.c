/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bikourar <bikourar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:23:52 by bikourar          #+#    #+#             */
/*   Updated: 2024/10/22 12:10:16 by bikourar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_token(char *bf, t_redir **l, t_env **ev, int *j)
{
	char	*s;

	(*l) = (t_redir *)ft_allocate(1, sizeof(t_redir));
	if (!(*l))
		return (write(2, "allocation fail\n", 17), -2);
	if ((isquote(bf[*j]) && bf[(*j + 1)] != '\0') && check_dd(&bf[*j], bf[*j]))
		return (check_in_quote(bf, bf[*j], j), 4);
	else if (bf[*j] == '>' && bf[(*j + 1)] == '>')
		(chos(&(*l)->tp, app), addp(j, 2));
	else if (bf[*j] == '<' && bf[(*j + 1)] == '<')
		(chos(&(*l)->tp, her_doc), addp(j, 2));
	else if (bf[*j] == '<' && !check_dir(bf[(*j + 1)]))
		(chos(&(*l)->tp, in), addp(j, 1));
	else if (bf[*j] == '>' && !check_dir(bf[(*j + 1)]))
		(chos(&(*l)->tp, out), addp(j, 1));
	else
		return (0);
	(addp(j, skp_w_sp(&bf[*j])), TRUE) && (s = process_dr(bf, ev, (*l), j));
	if (s == NULL)
		return (-1);
	(*l) = creat_node(s, l, ev);
	return (-3);
}

static t_redir	*get_token_dir(char *str, t_redir **lin, t_env **env, int i)
{
	t_redir	*new;
	int		k;

	(*lin) = NULL;
	while (str[i])
	{
		new = NULL;
		k = get_token(str, &new, env, &i);
		if (k == 0)
			i++;
		else if (k == -3)
		{
			ft_lstadd_redir(lin, new);
			if (new != NULL && new->del != NULL)
				i += ft_strlen(new->del);
		}
	}
	return (*lin);
}

static char	*pi_processing_dir(char *str, t_sh **h_n, t_env **env, int i)
{
	t_redir	*head;
	char	*stack;

	head = get_token_dir(str, &head, env, 0);
	if (ambiguous_redirect(&head) != 0)
		return (NULL);
	stack = (char *)ft_allocate(1, sizeof(char) * (ft_strlen(str) + 1));
	if (stack == NULL)
		return (NULL);
	change_and_rpl(str, stack, i);
	return ((*h_n)->dir = head, stack);
}

static t_sh	*update_argement(char *cmd, t_sh **new_n, int i, t_env **env)
{
	char	*cpy;
	char	*k;

	cpy = (char *)ft_allocate(1, sizeof(char) * (ft_strlen(cmd) + 1));
	if (!cpy)
		return (write(2, "allocation fail\n", 17), NULL);
	cpy = ft_strncpy(cpy, cmd, i);
	(*new_n) = (t_sh *)ft_allocate(1, sizeof(t_sh));
	if (!(*new_n))
		return (write(2, "allocation fail\n", 17), NULL);
	k = pi_processing_dir(cpy, new_n, env, 0);
	if (k == NULL)
		return (NULL);
	(*new_n) = pi_processing_in(k, new_n, env, 0);
	if (!(*new_n))
		return (write(2, "allocation fail\n", 17), NULL);
	return (*new_n);
}

t_sh	*token_data(char *str, t_env *env, t_sh **hd)
{
	t_sh	*nw;
	int		i;

	i = -1;
	nw = NULL;
	while (str[++i])
	{
		if (str[i] == '|' && !check_pipe(str, i, 0))
		{
			nw = update_argement(str, &nw, i, &env);
			if (!nw)
				return (NULL);
			ft_lstadd_back_msh(hd, nw);
			str = restory_cmd(str);
			i = -1;
		}
		else if (str[i] != '|' && str[i + 1] == '\0')
		{
			nw = update_argement(str, &nw, i + 1, &env);
			if (!nw)
				return (NULL);
			ft_lstadd_back_msh(hd, nw);
		}
	}
	return ((*hd));
}
