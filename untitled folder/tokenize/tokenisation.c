#include "minishell.h"

static int	get_token(char *inf, t_redir **l, t_env **env, int *j)
{
	char	*stock;

	(*l) = (t_redir *)ft_allocate(1, sizeof(t_redir));
	if (!(*l))
		return (write(2, "allocation fail\n", 17), -2);
	if ((isquote(inf[*j]) && inf[(*j + 1)] != '\0') && check_dd(&inf[*j], inf[*j]))
		return (check_in_quote(inf, inf[*j], j), 4);
	else if (inf[*j] == '>' && inf[(*j + 1)] == '>')
		chos(&(*l)->tp, app), counter(j, 2);
	else if (inf[*j] == '<' && inf[(*j + 1)] == '<')
		chos(&(*l)->tp, her_doc), counter(j, 2);
	else if (inf[*j] == '<' && !check_dir(inf[(*j + 1)]))
		chos(&(*l)->tp, in), counter(j, 1);
	else if (inf[*j] == '>' && !check_dir(inf[(*j + 1)]))
		chos(&(*l)->tp, out), counter(j, 1);
	else
		return (0);
	while (inf[*j] && (white_sp(inf[*j])))
		*j += 1;
	stock = pi_processing_redirect(inf, env, (*l), j);
	if (stock == NULL)
		return (-1);
	(*l) = creat_node(stock, l, env);
	if (!(*l) || ambiguous_redirect(l))
		return (-2);
	return (-3);
}

static t_redir	 *get_token_dir(char *str, t_redir **lin, t_env **env, int i)
{
	t_redir	*new;
	int		k;

	while (str[i])
	{
		new = NULL;
		k = get_token(str, &new, env, &i);
		if (k == 0)
			i++;
		else if (k == -2 || k == -1)
			return (NULL);
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
	int		j;

	head = NULL;
	head = get_token_dir(str, &head, env, 0);
	if (ambiguous_redirect(&head))
		return (NULL);
	stack = (char *)ft_allocate(1, sizeof(char) * (ft_strlen(str) * 2));
	if (stack == NULL)
		return (NULL);
	j = 0;
	while (str[i])
	{
		if (check_redir_quote(str, &i, 0))
			i += replace_space(stack, &j, &str[i]);
		else if (i != 0 && str[i] == ' ' && check_dir(str[i - 1]))
			i += replace_space(stack, &j, &str[i]);
		else if (i != 0 && !check_dir(str[i]) && check_dir(str[i - 1]))
			i += replace_space(stack, &j, &str[i]);
		else if (check_dir(str[i]) || white_sp(str[i]))
			stack[j++] = ' ', i++;
		else if (isquote(str[i]) && check_dd(&str[i], str[i]))
			i += strnlcpy(&stack, (unsigned int *)(&j), &str[i], str[i]);
		else
			stack[j++] = str[i++];
	}
	return ((*h_n)->dir = head, stack[j] = '\0', stack);
}

static t_sh	*update_argement(char *cmd, t_sh **new_n, int i, t_env **env)
{
	char	*stack;
	char	*k;

	stack = (char *)ft_allocate(1, sizeof(char) * (ft_strlen(cmd) + 1));
	if (!stack)
		return (write(2, "allocation fail\n", 17), NULL);
	stack = ft_strncpy(stack, cmd, i);
	(*new_n) = (t_sh *)ft_allocate(1, sizeof(t_sh)); 
	if (!(*new_n))
		return (write(2, "allocation fail\n", 17), NULL);
	k  = pi_processing_dir(stack, new_n, env, 0);
	if (k == NULL)
		return (NULL);
	(*new_n) = pi_processing_in(k, new_n, env);
	if (!(*new_n))
		return (write(2, "allocation fail\n", 17), NULL);
	return (*new_n);
}

t_sh	*token_data(char *str, t_env *env , t_sh **head)
{
	t_sh	*new;
	int		i;

	i = -1;
	new = NULL;
	while (str[++i])
	{
		if (str[i] == '|' && !check_pipe(str, i, 0))
		{
			new = update_argement(str, &new, i, &env);
			if (!new)
				return (head = &new, *head);
			ft_lstadd_back_msh(head, new);
			str = restory_cmd(str);
			i = -1;
		}
		else if (str[i] != '|' && str[i + 1] == '\0')
		{
			new = update_argement(str, &new, i + 1, &env);
			if (!new)
				return (head = &new, *head);
			ft_lstadd_back_msh(head, new);
		}
	}
	return (*head);
}