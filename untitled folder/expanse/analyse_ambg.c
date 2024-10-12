#include "minishell.h"

void	change(t_redir **hd)
{
	(*hd)->fd_her = -1;
	(*hd)->file_name = NULL;
	(*hd)->tp = ambiguos;
}

int	check_error_ambiguous(t_dir *nd, t_dir **head)
{
	int	i;

	if (nd == NULL)
		return (0);
	i = ft_lstsiz_dir((*head));
	if (nd->ambg == ambg_5)
		return (1);
	else if (nd->ambg == ambg_1 && i == 1)
		return (1);
	else if (nd->ambg == ambg_2 && (nd->prv != NULL && nd->prv->par->wd == wrd))
		return (1);
	else if (nd->ambg == ambg_3 && (nd->next != NULL && nd->next->par->wd == wrd))
		return (1);
	else if (nd->ambg == ambg_4 && i > 1)
		return (1);
	return (0);
}

static int	sort_case_ambg(char *in)
{
	int	j;
	int	i;

	if (in[0] == '\0')
		return (1);
	i = count_word(in, ' ');
	j = ft_strlen(in);
	if (i > 1)
		return (5);
	else if (white_sp(in[0]) && white_sp(in[j - 1]))
		return (4);
	else if (white_sp(in[0]) && !white_sp(in[j - 1]))
		return (2);
	else if (white_sp(in[j - 1]) && !white_sp(in[0]))
		return (3);
	return (6);
}

t_dir	*analyse_case_ambg(t_dir *tp, t_env **ev)
{
	char	*in;
	t_dir	*lst;

	lst = NULL;
	while (tp != NULL)
	{
		if (tp->par->st == not_join && tp->par->tp == exp)
		{
			in = search_in_eva(tp, ev);
			(ft_lstadd_back_dir(&lst, config_redirect(in, sort_case_ambg(in), tp)));
		}
		else if (tp->par->st == join && tp->par->tp == exp)
		{
			in = search_in_eva(tp, ev);
			(ft_lstadd_back_dir(&lst, config_redirect(in, 0, tp)));
		}
		else
			ft_lstadd_back_dir(&lst, config_redirect(tp->input, 0, tp));
		tp = tp->next;
	}
	return (lst);
}

t_dir	*check_ambiguous_redirect(t_dir **l, char *in, t_redir **d)
{
	t_dir	*tp;

	if ((*l) ==  NULL)
		return (NULL);
	tp = (*l);
	while (tp)
	{
		if (tp->ambg == 0)
			tp = tp->next;
		else
		{
			if (check_error_ambiguous(tp, l) != 0)
				return (put_ambeg(in), change(d), tp);
			else
				tp = tp->next;
		}
	}
	return (tp = (*l), tp);
}

void	copy_status(char *in, int *j, t_exp **l)
{
	char	*dst;
	int		chmod;

	chmod = 0;
	dst = NULL;
	if (in[*j] == '$' && in[(*j + 1)] == '?')
		dst = ft_strdup("$?");
	if (faile((*l), dst, true))
		return ;
	*j += 2;
	(premission(&chmod, 0, 0, 0));
	(ft_lstadd_back_texp(l, upgrade_input(dst, &chmod)));
}