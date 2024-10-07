#include "minishell.h"

char	**mise_ajour_input(t_dir **lst)
{
	char	**data;
	t_dir	*tmp;
	int		i;

	data = (char **)malloc((ft_lstsiz_dir((*lst)) + 1) * sizeof(char *));
	if (!data)
		return (write(2, "faile allocation 303\n", 22), NULL);
	i = 0;
	tmp = (*lst);
	while (tmp)
	{
		if (!ft_strcmp(tmp->input, """") || !ft_strcmp(tmp->input, "''"))
			tmp = tmp->next;
		else
		{
			data[i++] = ft_strdup(tmp->input);
			if (data[i - 1] == NULL)
				return (write(2, "faile allocation 404\n", 22), NULL);
			tmp = tmp->next;
		}
	}
	data[i] = 0;
	return (data);
}

static void	parse_expand_dir(char *src, int *i, t_dir **head)
{
	if (src[*i] && src[*i] == '\"')
		*i += 1;
	while (src[*i] && src[*i] != '\"')
	{
		if (src[*i] == '$' && is_numeric(src[(*i + 1)]))
			i += 2;
		else if (valid_condtion(src, *i))
			expand_wqoute(src, i, head);
		else if (src[*i] == '\'')
			parsse_wesq(src, i, head);
		else
			copy_std_norm(src, i, head);
		if (failed(*head, NULL, false))
			return ;
	}
	if (src[*i] && src[*i] == '\"')
		i += 1;
}

t_dir	*upgrade_list(char **in, t_dir **lst)
{
	t_dir	*head;
	int		i;
	int		j;

	i = 0;
	if ((*lst) == NULL || in == NULL)
		return (NULL);
	head = NULL;
	while (in[i])
	{
		j = 0;
		if (in[i][0] == '$')
			expand_dir(in[i], &j, &head);
		else if (in[i][0] == '\"')
			parse_expand_dir(in[i], &j, &head);
		else if (in[i][0] == '\'')
			cin_singlq(in[i], &j, &head);
		else
			copy_gen(in[i], &j, &head);
		if (failed(*lst, NULL, false))
			return (NULL);
		i++;
	}
	(*lst) = head;//free lst and pointe to head
	return ((*lst));
}

char	*search_in_eva(t_dir *nd, t_env **ev)
{
	t_env	*tp;

	tp = (*ev);
	while (tp)
	{
		if (tp->value != NULL && tp->value[0] != '\0' && !ft_strcmp(nd->input, tp->var))
			return (ft_strdup(tp->value));
		tp = tp->next;
	}
	return (NULL);
}

void	owner_premt(int *chmod, int	tp, int	wd, int	st)
{
	*chmod = tp + wd + st;
}