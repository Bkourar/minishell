#include "minishell.h"

void	std_copy(char *src, int *i, t_dir **lst)
{
	char	*dst;
	int		j;
	int		chmod;

	dst = (char *)malloc(sizeof(char) * ft_strlen(src) + 1);
	if (failed(*lst, dst, true))
		return ;
	chmod = 0;
	j = 0;
	while (src[*i])
	{
		if (src[*i] == '$' && (src[(*i + 1)] == '\'' || src[(*i + 1)] == '\"'))
			*i += 1;
		else if (j != 0 && isquote(src[*i]))
			break ;
		else if (white_sp(src[*i]))
			break;
		else
		{
			dst[j++] = src[*i];
			*i += 1;
		}
	}
	(dst[j] = '\0', owner_premt(&chmod, 0, 2, 0));
	(ft_lstadd_back_dir(lst, upgrade_redirect(dst, &chmod, 0)));
}

t_dir	*set_data(char *in, t_dir **lst)
{
	t_dir	*head;
	int		i;

	i = 0;
	while (in[i])
	{
		if (in[i] == '\'')
			copy_whit_singlq(in, &i, lst);
		else if (in[i] == '\"')
			copy_whit_doublq(in, &i, lst);
		else
			std_copy(in, &i, lst);
		if (failed(*lst, NULL, false))
			return (NULL);
	}
	return (head = (*lst), head);
}

void	copyin_sqoute(char *src, int *i, t_dir **lst)
{
	char	*dst;
	int		chmod;
	int		j;

	dst = (char *)malloc(sizeof(char) * ft_strlen(src) + 1);
	if (failed(*lst, dst, true))
		return ;
	chmod = 0;
	j = 0;
	while (src[*i] && src[*i] != '\"')
	{
		if (j != 0 && src[*i] == '\'')
			break ;
		else
			dst[j++] = src[*i];
		*i += 1;
	}
	(dst[j] = '\0', owner_premt(&chmod, 0, 2, 1));
	(ft_lstadd_back_dir(lst, upgrade_redirect(dst, &chmod, 0)));
}

void	pars_whit_sq(char *src, int *i, t_dir **lst)
{
	while (src[*i] && src[*i] != '\"')
	{
		if (src[*i] == '\'')
			copy_singleq(src, i, lst);
		else
			copyin_sqoute(src, i, lst);
		if (failed(*lst, NULL, false))
			return ;
	}
}

void	copy_std_n(char *src, int *i, t_dir **lst)
{
	char	*dst;
	int		chmod;
	int		j;

	dst = (char *)malloc(sizeof(char) * ft_strlen(src) + 1);
	if (failed(*lst, dst, true))
		return ;
	chmod = 0;
	j = 0;
	while (src[*i] && src[*i] != '\"')
	{
		if (j != 0 && (src[*i] == '\''|| src[*i] == '$' || src[*i] == '\"'))
			break ;
		else
		{
			dst[j++] = src[*i];
			*i += 1;
		}
	}
	(dst[j] = '\0', owner_premt(&chmod, 0, 2, 1));
	(ft_lstadd_back_dir(lst, upgrade_redirect(dst, &chmod, 0)));
}
