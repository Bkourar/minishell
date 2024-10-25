/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool1_process_reds.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bikourar <bikourar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 23:13:48 by bikourar          #+#    #+#             */
/*   Updated: 2024/10/25 17:31:30 by bikourar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_gen(char *src, int *i, t_dir **lst)
{
	char	*dst;
	int		chmod;
	int		j;

	dst = (char *)ft_allocate(1, sizeof(char) * ft_strlen(src) + 1);
	if (failed(*lst, dst, TRUE))
		return ;
	chmod = 0;
	j = 0;
	while (src[*i])
	{
		dst[j++] = src[*i];
		*i += 1;
	}
	dst[j] = '\0';
	o_p(&chmod, 0, 2, 0);
	(add_dir(lst, up_redire(dst, &chmod, 0)));
}

void	cin_singlq(char *src, int *i, t_dir **lst)
{
	char	*dst;
	int		chmod;
	int		j;

	if (src[*i] && src[*i] == '\'')
		*i += 1;
	dst = (char *)ft_allocate(1, sizeof(char) * ft_strlen(src) + 1);
	if (failed(*lst, dst, TRUE))
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
	dst[j] = '\0';
	o_p(&chmod, 0, 2, 1);
	(add_dir(lst, up_redire(dst, &chmod, 0)));
	if (src[*i] && src[*i] == '\'')
		*i += 1;
}

void	expand_dir(char *arr, int *i, t_dir **lst)
{
	char	*dst;
	int		chmod;
	int		j;

	if (arr[*i] && arr[*i] == '$')
		*i += 1;
	dst = (char *)ft_allocate(1, sizeof(char) * (ft_strlen(arr) + 1));
	if (failed(*lst, dst, TRUE))
		return ;
	chmod = 0;
	j = 0;
	while (arr[*i])
	{
		dst[j++] = arr[*i];
		*i += 1;
	}
	dst[j] = '\0';
	o_p(&chmod, 4, 0, 0);
	(add_dir(lst, up_redire(dst, &chmod, 0)));
}

int	failed(t_dir *l, void *arg, BOOL flg)
{
	if (l && (l->prv != NULL && l->prv->ck != 1)
		&& (flg == TRUE && arg == NULL))
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
	else if (arg == NULL && flg == TRUE)
	{
		if (l != NULL)
			l->ck = 1;
		write(2, "faile allocation\n", 18);
		write(2, "faile 2\n", 9);
		return (1);
	}
	return (0);
}

char	*s_and_r(t_exp **txp, t_env **env)
{
	t_env	*tp;
	char	*str;

	tp = (*env);
	str = NULL;
	while (tp)
	{
		if (!ft_strcmp((*txp)->input, tp->var))
		{
			str = ft_strdup(tp->value);
			if (!str)
				return (write(2, "faile allocation\n", 18), NULL);
			return (str);
		}
		tp = tp->next;
	}
	if (tp == NULL)
		str = ft_strdup("ß");
	if (!str)
		return (write(2, "faile allocation\n", 18), NULL);
	return (str);
}
