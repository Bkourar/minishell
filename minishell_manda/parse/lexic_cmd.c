/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexic_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bikourar <bikourar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:25:22 by bikourar          #+#    #+#             */
/*   Updated: 2024/10/13 16:25:23 by bikourar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	checker_typing(char const *santax)
{
	if (!ft_strcmp("<>", santax) || !ft_strcmp("><", santax))
		return (1);
	else if (!ft_strcmp("||", santax) || !ft_strcmp(">|", santax))
		return (1);
	else if (!ft_strcmp("<|", santax) || !ft_strcmp("|>", santax))
		return (1);
	else if (!ft_strcmp("|<", santax))
		return (2);
	return (0);
}

static void	complete_type(t_tk **lst, int type)
{
	if (type == 1)
		(*lst)->type = err;
	else if (type == 2)
		(*lst)->type = L_err;
}

static t_tk	*parse_commands_2(t_tk **n, char const *string)
{
	if (!ft_strcmp("<", string))
		(*n)->type = input;
	else if (!ft_strcmp(">", string))
		(*n)->type = output;
	else if (!ft_strcmp("<<", string))
		(*n)->type = heredoc;
	else if (!ft_strcmp(">>", string))
		(*n)->type = append;
	else if (checker_typing(string) > 0)
		complete_type(n, checker_typing(string));
	else if (!ft_strcmp("|", string))
		(*n)->type = Pipe;
	else if (!ft_strcmp("\"", string) || !ft_strcmp("'", string))
	{
		if (string[0] == '\"')
			(*n)->type = d_quot;
		else
			(*n)->type = s_quot;
		(*n)->stat = ft_strdup("spicial");
	}
	else if (!ft_strcmp("$", string))
		(*n)->type = dolar;
	return (*n);
}

static t_tk	*parse_commands_1(char const *st)
{
	t_tk	*new;

	new = NULL;
	if (!check_op(st[0]) && (st[1] == '\0' || check_redir(st)))
	{
		new = (t_tk *)ft_allocate(1, sizeof(t_tk));
		if (!new)
			return (NULL);
		(new->token = ft_strdup(st)) && (new->stat = ft_strdup("genral"));
		if (new->token == NULL || new->stat == NULL)
			return (write(2, "error in allocation", 20), NULL);
		new->checker = 0;
		new = parse_commands_2(&new, st);
		if (!new)
			return (NULL);
		new->nx = NULL;
	}
	else
	{
		if (pars_word((char *)st, &new))
			return (NULL);
	}
	return (new);
}

t_tk	*create_commands(char **words)
{
	t_tk	*head;
	t_tk	*node;
	int		i;

	if (!words || !*words)
		return (NULL);
	head = NULL;
	node = NULL;
	i = -1;
	while (words[++i])
	{
		node = parse_commands_1(words[i]);
		if (!node)
			return (NULL);
		ft_lstadd_back_ttk(&head, node);
	}
	return (head);
}
