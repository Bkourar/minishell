#include "minishell.h"

void	copy_gen(char *src, int *i, t_dir **lst)
{
	char	*dst;
	int		chmod;
	int		j;

	dst = (char *)ft_allocate(1, sizeof(char) * ft_strlen(src) + 1);
	if (failed(*lst, dst, true))
		return ;
	chmod = 0;
	j = 0;
	while (src[*i])
	{
		dst[j++] = src[*i];
		*i += 1;
	}
	(dst[j] = '\0', owner_premt(&chmod, 0, 2, 0));
	(ft_lstadd_back_dir(lst, upgrade_redirect(dst, &chmod, 0)));
}

void	cin_singlq(char *src, int *i, t_dir **lst)
{
	char	*dst;
	int		chmod;
	int		j;

	if (src[*i] && src[*i] == '\'')
		*i += 1;
	dst = (char *)ft_allocate(1, sizeof(char) * ft_strlen(src) + 1);
	if (failed(*lst, dst, true))
		return ;
	chmod = 0;
	j = 0;
	while (src[*i])
	{
		if (j != 0 && src[*i] == '\'')
			break ;
		else
			dst[j++] = src[*i];
		*i += 1;
	}
	(dst[j] = '\0', owner_premt(&chmod, 0, 2, 1));
	(ft_lstadd_back_dir(lst, upgrade_redirect(dst, &chmod, 0)));
	if (src[*i] && src[*i] == '\'')
		*i += 1;
}

void	expand_dir(char *arr, int *i, t_dir **lst)
{
	char	*dst;
	int		chmod;
	int		j;

	if (arr[*i] && (arr[*i] == '$' || is_numeric(arr[(*i + 1)])))
		*i += 1;
	dst = (char *)ft_allocate(1, sizeof(char) * ft_strlen(arr) + 1);
	if (failed(*lst, dst, true))
		return ;
	chmod = 0;
	j = 0;
	while (arr[*i])
	{
		dst[j++] = arr[*i];
		*i += 1;
	}
	(dst[j] = '\0', owner_premt(&chmod, 4, 0, 0));
	(ft_lstadd_back_dir(lst, upgrade_redirect(dst, &chmod, 0)));
}

int	failed(t_dir *l, void *arg, bool flg)
{
	if (l && (l->prv != NULL && l->prv->ck != 1) 
		&& (flg == true && arg == NULL))
	{
		l->prv->ck = 1;
		write(2, "faile allocation\n", 18);
		write(2, "faile 1\n", 9);
		return (1);
	}
	else if (l && l->prv != NULL && l->prv->ck == 1)
		return (1);
	else if (l != NULL && l->ck == 1)
		return (1);
	else if (arg == NULL && flg == true)
	{
		if (l != NULL)
			l->ck = 1;
		write(2, "faile allocation\n", 18);
		write(2, "faile 2\n", 9);
		return (1);
	}
	return (0);
}

