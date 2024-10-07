#include "minishell.h"

int	valid_condtion(char *str, int p)
{
	if (str[p] == '$' && valid_expand(str[p + 1]))
		return (1);
	return (0);
}

int	is_numeric(char c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	ambiguous_redirect(t_redir **hd)
{
	t_redir	*tp;

	tp = (*hd);
	while (tp)
	{
		if (tp->file_name == NULL && tp->fd_her == -1)
			return (1);
		tp = tp->next;
	}
	return (0);
}

int	valid_expand(char c)
{
	if (is_numeric(c) || c == '_' || is_alpha(c))
		return (1);
	return (0);
}

int	is_alpha(char c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}