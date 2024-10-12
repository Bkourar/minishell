#include "minishell.h"

t_tk	*pi_processing_cmd(t_tk **lst)
{
	t_tk	*tmp;
	char	c1;
	char	c2;
	int		j;

	tmp = (*lst);
	j = 0;
	while (tmp != NULL && j != 1)
	{
		c1 = tmp->token[0];
		c2 = tmp->token[1];
		if (tmp->type == err)
			j = pi_processing_err_3(c1, c2);
		tmp = tmp->nx;
	}
	tmp = ft_lstlast(lst);
	if (j == 0 && tmp->type == L_err)
		return (synatx_error(tmp->token), NULL);
	else if (j == 1 || pi_processing_err_1(lst, &tmp))
		return (NULL);
	else if (pi_processing_err_2(lst) || pi_processing_err_4(lst))
		return (NULL);
	else if (pi_processing_err_5(lst))
		return (NULL);
	return ((*lst));
}

char	loop(t_tk **tmp, t_p type, int *j)
{
	char c;

	while ((*tmp) != NULL && *j != 2)
	{
		if ((*tmp)->type == type)
		{
			c = (*tmp)->token[0];
			*j += 1;
		}
		(*tmp) = (*tmp)->nx;
	}
	return (c);
}