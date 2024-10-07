#include "minishell.h"

static void	copy_quote(char *in, int *i, t_tk **l, char c)
{
	char	*dst;
	int		j;

	dst = ck_and_dp(in[*i]);
	if (failing((*l), dst, true))
		return ;
	(ft_lstadd_back_ttk(l, ft_lstnew(dst, true)), free(dst), counter(i, 1));
	if (in[*i] == '\0')
		return ;
	dst = (char *)malloc(sizeof(char) * (ft_strlen(in) + 1));
	if (failing((*l), dst, true))
		return ;
	j = 0;
	while (in[*i])
	{
		if (in[*i] == c)
			break ;
		dst[j++] = in[*i];
		*i += 1;
	}
	if (in[(*i - 1)] != c)
		(dst[j] = '\0', ft_lstadd_back_ttk(l,ft_lstnew(dst, true)), free(dst));
	if (in[*i] == '\0')
		return ;
	dst = ck_and_dp(in[*i]);
	if (failing((*l), dst, true))
		return ;
	(ft_lstadd_back_ttk(l, ft_lstnew(dst, true)), free(dst), counter(i, 1));
}

static void	copy_dir(char *in, int *i, t_tk **l)
{
	char	*dst;
	
	dst = NULL;
	if (in[*i] == '<' && in[(*i + 1)] == '<')
	{
		dst = ft_strdup("<<");
		*i += 2;
	}
	else if (in[*i] == '>' && in[(*i + 1)] == '>')
	{
		dst = ft_strdup(">>");
		*i += 2;
	}
	else if (in[*i] == '<' && in[(*i + 1)] != '<')
	{
		dst = ft_strdup("<");
		*i += 1;
	}
	else if (in[*i] == '>' && in[(*i + 1)] != '>')
	{
		dst = ft_strdup(">");
		*i += 1;
	}
	if (failing((*l), dst, true))
		return ;
	(ft_lstadd_back_ttk(l, ft_lstnew(dst, true)), free(dst));
}

static void	copy_pd(char *in, int *i, t_tk **l)
{
	char	*dst;

	dst = NULL;
	if (in[*i] == '$')
		dst = ft_strdup("$");
	else if (in[*i] == '|')
		dst = ft_strdup("|");
	*i += 1;
	if (failing((*l), dst, true))
		return ;
	(ft_lstadd_back_ttk(l,ft_lstnew(dst, true)), free(dst));
}

static void	copy_stdin(char *in, int *i, t_tk **l)
{
	char	*dst;
	int		j;

	dst = (char *)malloc(sizeof(char) * (ft_strlen(in) + 1));
	if (failing((*l), dst, true))
		return ;
	j = 0;
	while (in[*i])
	{
		if (!check_op(in[*i]) || white_sp(in[*i]))
			break ;
		dst[j++] = in[*i];
		*i += 1;
	}
	(dst[j] = '\0', ft_lstadd_back_ttk(l, ft_lstnew(dst, true)), free(dst));
}

char	**token_input(char *in, t_tk **lst)
{
	int		i;

	i = 0;
	// printf("%c\n", in[0]);
	// exit(1);
	while (in[i] != '\0')
	{
		if (isquote(in[i]))
			copy_quote(in, &i, lst, in[i]);
		else if (check_dir(in[i]))
			copy_dir(in, &i, lst);
		else if (check_pd(in[i]))
			copy_pd(in, &i, lst);
		else if (white_sp(in[i]))
			i++;
		else
			copy_stdin(in, &i, lst);
		if (failing((*lst), NULL, false))
			return (NULL);
	}
	return (double_arr(lst));
}
