#include "minishell.h"

// static void	up_grade(t_tk **n, char *string)
// {
// 	if (!ft_strcmp("<<", string))
// 		(*n)->type = heredoc;
// 	else if (!ft_strcmp(">>", string))
// 		(*n)->type = append;
// 	else if (!ft_strcmp("<", string))
// 		(*n)->type = input;
// 	else if (!ft_strcmp(">", string))
// 		(*n)->type = output;
// 	else if (!ft_strcmp("\"", string) || !ft_strcmp("'", string))
// 	{
// 		if (!ft_strcmp("\"", string))
// 			(*n)->type = d_quot;
// 		else
// 			(*n)->type = s_quot;
// 		(//free((*n)->stat),
// 			(*n)->stat = ft_strdup("spicial"));//alloction whit gc
// 	}
// 	else if (!ft_strcmp("$", string))
// 		(*n)->type = dolar;
// 	else if (!ft_strcmp("|", string))
// 		(*n)->type = Pipe;
// 	else
// 		(*n)->type = word;
// }

static void	up_date(char *str, t_tk **lst)
{
	t_tk	*node;

	if (!str)
	{
		if ((*lst)->pv != NULL)
			(*lst)->pv->checker = 1;
		return ;
	}
	node = ft_lstnew(str, false);
	node->stat = ft_strdup("general");//alloction whit gc
	if (node->stat)
		node->type = word; // up_grade(&node, str);
	if (!node || !node->token || !node->stat)
	{
		if ((*lst)->pv != NULL)
			(*lst)->pv->checker = 1;
		return ;
	}
	else
		node->checker = 0;
	ft_lstadd_back_ttk(&(*lst), node);
}

static int	take_str(char *str, int *i, t_tk **node)
{
	if (!str)
	{
		if ((*node) && (*node)->pv != NULL)
			(*node)->pv->checker = 1;
		return (1);
	}
	// if (!ft_strcmp("\'", str) || !ft_strcmp("\"", str))
	// 	(up_date(str, node), counter(i, 1));
	// else if (isquote(str[*i]) && str[(*i + 1)] != '\0')
	// {
	// 	up_date(ck_and_dp(str[*i]), node);
	// 	up_date(dup_quote(str, i, str[*i]), node);
	// 	if (str[*i] != '\0' && isquote(str[*i]))
	// 		(up_date(ck_and_dp(str[*i]), node), counter(i, 1));
	// }
	// else if (!ft_strcmp("<<", str) || !ft_strcmp(">>", str))
	// 	(up_date(str, node), counter(i, 2));
	// else if (!ft_strcmp("<", str) || !ft_strcmp(">", str))
	// 	(up_date(str, node), counter(i, 1));
	// else if (!ft_strcmp("$", str) || !ft_strcmp("|", str))
	// 	(up_date(str, node), counter(i, 1));
	// else
	(void)i;
		(up_date(str, node));
	return (0);
}

// static char	*get_word(char	*str, int *j, t_tk **l)
// {
// 	char	*stock;
// 	int		i;

// 	if ((*l) && ((*l)->pv != NULL && (*l)->pv->checker == 1))
// 		return (NULL);
// 	stock = ft_allocate(1, sizeof(char) * (ft_strlen(str) + 1));//alloction whit gc
// 	if (!stock)
// 	{
// 		if ((*l)->pv != NULL)
// 			(*l)->pv->checker = 1;
// 		return (write(2, "error in allocation", 20), NULL);
// 	}
// 	i = 0;
// 	while (check_op(str[*j]) && str[*j])
// 	{
// 		stock[i++] = str[*j];
// 		*j += 1;
// 	}
// 	stock[i] = '\0';
// 	return (stock);
// }

int	pars_word(char *input, t_tk **l, int i, int j)
{
	// while (input[i])
	// {
	// 	if (input[i] == '<' && input[i + 1] == '<')
	// 		j = take_str(ft_strdup("<<"), &i, l);
	// 	else if (input[i] == '>' && input[i + 1] == '>')
	// 		j = take_str(ft_strdup(">>"), &i, l);
	// 	else if (input[i] == '<')
	// 		j = take_str(ft_strdup("<"), &i, l);
	// 	else if (input[i] == '>')
	// 		j = take_str(ft_strdup(">"), &i, l);
	// 	else if (input[i] == '|')
	// 		j = take_str(ft_strdup("|"), &i, l);
	// 	else if (isquote(input[i]) && input[i + 1] == '\0')
	// 		j = take_str(ck_and_dp(input[i]), &i, l);
	// 	else if (input[i] == '$')
	// 		j = take_str(ft_strdup("$"), &i, l);
	// 	else if (isquote(input[i]) && input[i + 1] != '\0')
			j = take_str(input, &i, l);
		// else
		// 	j = take_str(get_word(input, &i, l), &i, l);
		// if (j == 1 || ((*l)->pv != NULL && (*l)->pv->checker == 1))
		// 	return (1);
	// }
	return (0);
}
