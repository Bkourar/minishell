#include "minishell.h"

// static void	free_exp(t_exp **l)
// {
// 	t_exp	*tp;
// 	t_exp	*tp1;

// 	tp = (*l);
// 	tp1 = (*l)->next;
// 	while (tp)
// 	{
// 		free(tp1->input);
// 		free(tp1);
// 		tp = tp1;
// 		tp1 = tp1->next;
// 	}
// 	free(tp->input);
// 	free(tp);
// }


t_exp	*ifconfigration(t_exp **l, t_env **ev)
{
	t_exp	*head;
	char	**s;
	int		wx;

	head = NULL;
	while ((*l))
	{
		if ((*l)->set->tp == exp && (*l)->set->st == not_join)
		{
			s = parse_value(&(*l), ev);
			autortion(s, &head, own_exp(4, (*l)->set->sp, 0));
		}
		else if ((*l)->set->tp == exp && (*l)->set->st == join)
		{
			wx = own_exp(4, (*l)->set->sp, 1);
			ft_lstadd_back_texp(&head, upgrade_input(s_and_r(&(*l), ev), &wx));
		}
		else
		{
			wx = own_exp((*l)->set->tp, (*l)->set->sp, (*l)->set->st);
			ft_lstadd_back_texp(&head, upgrade_input((*l)->input, &wx));
		}
		(*l) = (*l)->next;
	}
	return ((*l) = head, (*l));//here free l
}

static void	next(t_exp **nd)
{
	(*nd) = (*nd)->next;
}

static t_exp	*concatition(t_exp **lst, char *str)
{
	t_exp	*nd1;
	t_exp	*head;
	
	head= NULL;
	nd1 = (*lst);
	while (nd1)
	{
		str = NULL;
		if (valid_join(nd1))
		{
			while (nd1 && valid_join(nd1))
			{
				str = ft_strjoin(str, nd1->input);
				if (!str)
					return (write(2, "faile allocation\n", 18), NULL);
				next(&nd1);
			}
			ft_lstadd_back_texp(&head, config(str)), free(str);
		}
		else
			(ft_lstadd_back_texp(&head, config(nd1->input)), next(&nd1));
	}
	return (head);//free lst 9dima
}

static char	**result_expand(t_exp **hd)
{
	t_exp	*tp;
	char	**spl;
	int		i;

	spl = (char **)malloc((ft_lstsize_exp((*hd)) + 1) * sizeof(char *));
	if (!spl)
		return (write(2, "faile allocation\n", 18), NULL);
	i = 0;
	tp = (*hd);
	while (tp)
	{
		if (!ft_strcmp(tp->input, " "))
			tp = tp->next;
		else
		{
			spl[i++] = ft_strdup(tp->input);
			if (!spl[i - 1])
				return (write(2, "faile allocation\n", 18), NULL);
			tp = tp->next;
		}
	}
	return (spl[i] = 0, spl);
}

char	**pi_processing_expand(char *str, t_env **env)
{
	char	**cmd_aft_exp;
	char	*in;
	t_exp	*head;

	head = NULL;
	in = NULL;
	if (str == NULL)
		return (NULL);
	head = update_input(str, &head);
	if (!head)
		return (NULL);
	head = update_list(update_array(&head, 0), &head);
	if (!head)
		return (NULL);
	head = ifconfigration(&head, env);
	if (!head)
		return (NULL);
	head = concatition(&head, in);
	if (!head)
		return (NULL);
	cmd_aft_exp = result_expand(&head);
	if (!cmd_aft_exp)
		return (NULL);
	return (cmd_aft_exp);//free head;
}
