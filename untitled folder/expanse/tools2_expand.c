#include "minishell.h"

void	expand(char *arr, int *i, t_exp **lst)
{
	char	*dst;
	int		chmod;
	int		j;

	if (arr[*i] && (arr[*i] == '$' || is_numeric(arr[(*i + 1)])))
		*i += 1;
	dst = (char *)ft_allocate(1, sizeof(char) *  ft_strlen(arr) + 1);
	if (faile((*lst), dst, true))
		return ;
	chmod = 0;
	j = 0;
	while (arr[*i])
	{
		dst[j++] = arr[*i];
		*i += 1;
	}
	(dst[j] = '\0', premission(&chmod, 4, 0, 0));
	(ft_lstadd_back_texp(lst, upgrade_input(dst, &chmod)));
}

void	expand_sq(char *arr, int *i, t_exp **lst)
{
	char	*dst;
	int		chmod;
	int		j;

	if (arr[*i] && (arr[*i] == '$' || is_numeric(arr[(*i + 1)])))
		*i += 1;
	dst = (char *)ft_allocate(1, sizeof(char) *  ft_strlen(arr) + 1);
	if (faile((*lst), dst, true))
		return ;
	chmod = 0;
	j = 0;
	while (arr[*i])
	{
		if (is_numeric(arr[(*i - 1)]) && is_numeric(arr[*i]))
			break ;
		if (!valid_expand(arr[*i]))
			break ;
		dst[j++] = arr[*i];
		*i += 1;
	}
	(dst[j] = '\0', premission(&chmod, 4, 0, 1));
	(ft_lstadd_back_texp(lst, upgrade_input(dst, &chmod)));
}

void	parsse_sq(char *src, int *i, t_exp **lst)
{
	while (src[*i] && src[*i] != '\"')
	{
		if (src[*i] == '\'')
			copy_single_q(src, i, lst);
		else if (valid_condtion(src, *i))
			expand_sq(src, i, lst);
		else
			copy_in_sq(src, i, lst);
		if (faile((*lst), NULL, false))
			return ;
	}
}

void	copy_std(char *src, int *i, t_exp **lst)
{
	char	*dst;
	int		chmod;
	int		j;

	dst = (char *)ft_allocate(1, sizeof(char) *  ft_strlen(src) + 1);
	if (faile((*lst), dst, true))
		return ;
	chmod = 0;
	j = 0;
	while (src[*i] && src[*i] != '\"')
	{
		if (j != 0 && (isquote(src[*i]) || src[*i] == '$'))
			break ;
		else
		{
			dst[j++] = src[*i];
			*i += 1;
		}
	}
	(dst[j] = '\0', premission(&chmod, 0, 0, 1));
	(ft_lstadd_back_texp(lst, upgrade_input(dst, &chmod)));
}

void	copy_single_q(char *src, int *i, t_exp **lst)
{
	char	*dst;
	int		chmod;
	int		j;

	dst = (char *)ft_allocate(1, sizeof(char) *  2);
	if (faile((*lst), dst, true))
		return ;
	chmod = 0;
	j = 0;
	if (src[*i] == '\'')
		dst[j++] = src[*i];
	(dst[j] = '\0', premission(&chmod, 0, 0, 1));
	(ft_lstadd_back_texp(lst, upgrade_input(dst, &chmod)));
	*i += 1;
}
