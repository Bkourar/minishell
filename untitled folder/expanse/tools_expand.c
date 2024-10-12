#include "minishell.h"

void	upgrade_setting(t_set **setting, int rwx)
{
	if (rwx == 4 || rwx == 6 || rwx == 5 || rwx == 7)
		(*setting)->tp = exp;
	else
		(*setting)->tp = not_exp;
	if (rwx == 2 || rwx == 6 || rwx == 3 || rwx == 7)
		(*setting)->sp = skip;
	else
		(*setting)->sp = not_skip;
	if (rwx == 1 || rwx == 5 || rwx == 3 || rwx == 7)
		(*setting)->st = join;
	else
		(*setting)->st = not_join;
}

void	skip_wspace(char *str, int *j, t_exp **lst)
{
	int		i;
	char	*dst;
	int		chmod;

	dst = (char *)ft_allocate(1, sizeof(char) *  ft_strlen(str) + 1);
	if (faile((*lst), dst, true))
		return ;
	i = 0;
	chmod = 0;
	while (str[*j])
	{
		if (white_sp(str[*j]))
		{
			dst[i++] = str[*j];
			*j += 1;
		}
		else
			break ;
	}
	(dst[i] = '\0', premission(&chmod, 0, 2, 0));
	(ft_lstadd_back_texp(lst, upgrade_input(dst, &chmod)));
}

void	premission(int *chmod, int tp, int sp, int st)
{
	*chmod = tp + sp + st;
}

char	**update_array(t_exp **lst, int i, bool b)
{
	char	**data;
	t_exp	*tmp;

	data = (char **)ft_allocate(1, (ft_lstsize_exp((*lst)) + 1) * sizeof(char *));
	if (!data)
		write(2, "faile allocation\n", 18), exit(1);
	tmp = (*lst);
	while (tmp)
	{
		if (b == true && (!ft_strcmp(tmp->input, """") || !ft_strcmp(tmp->input, "''")))
			tmp = tmp->next;
		else
		{
			if (tmp->set->sp == skip)
				data[i++] = ft_strdup(" ");
			else
				data[i++] = ft_strdup(tmp->input);
			if (!data[i - 1])
				return (NULL);
			tmp = tmp->next;
		}
	}
	data[i] = 0;
	return (data);
}

int	own_exp(int tp, int sp, int st)
{
	int	chmod;

	chmod = tp + sp + st;
	return (chmod);
}
