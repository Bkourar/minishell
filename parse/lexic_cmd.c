#include "minishell.h"

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
		if (!ft_strcmp("\"", string))
			(*n)->type = d_quot;
		else
			(*n)->type = s_quot;
		free((*n)->stat);
		(*n)->stat = ft_strdup("spicial");//alloction whit gc
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
		new = (t_tk *)malloc(sizeof(t_tk));//alloction whit gc
		if (!new)
			return (NULL);//free gc
		new->token = ft_strdup(st);//alloction whit gc
		new->stat = ft_strdup("genral");//alloction whit gc
		new->checker = 0;
		if (new->token == NULL || new->stat == NULL)
			return (write(2, "error in allocation", 20), NULL);//free gc
		new = parse_commands_2(&new, st);
		if (!new)
			return (NULL);//free gc
		new->nx = NULL;
	}
	else
	{
		if (pars_word((char *)st, &new, 0, 0) == 1)
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
	i = 0;
	while (words[i])
	{
		node = parse_commands_1(words[i]);
		if (!node)
			return (NULL);//free gc
		ft_lstadd_back_ttk(&head, node);
		i++;
	}
	return (head);
}

void	complete_type(t_tk **lst, int type)
{
	if (type == 1)
		(*lst)->type = err;
	else if (type == 2)
		(*lst)->type = L_err;
}