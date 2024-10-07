#include "minishell.h"

void	copy_in_sq(char *src, int *i, t_exp **lst)
{
	char	*dst;
	int		chmod;
	int		j;

	dst = (char *)malloc(sizeof(char) *  ft_strlen(src) + 1);
	if (faile((*lst), dst, true))
		return ;
	chmod = 0;
	j = 0;
	while (src[*i] && src[*i] != '\"')
	{
		if (j != 0 && (src[*i] == '\'' || src[*i] == '$'))
			break ;
		else
			dst[j++] = src[*i];
		*i += 1;
	}
	(dst[j] = '\0', premission(&chmod, 0, 0, 1));
	(ft_lstadd_back_texp(lst, upgrade_input(dst, &chmod)), free(dst));
}

char	**parse_value(t_exp **hd, t_env **env)
{
	char	**spl;
	t_env	*tp;

	tp = (*env);
	while (tp)
	{
		if (!ft_strcmp((*hd)->input, tp->var))
		{
			if (condition_for_split(&(*hd)))
				return (spl[0] = give_arg(env, (*hd), &spl), spl[1] = 0, spl);
			spl = ft_split(tp->value, ' ');
			if (!spl)
				return (write(2, "faile allocation\n", 18), NULL);
			return (spl);
		}
		tp = tp->next;
	}
	spl = (char **)malloc((1 + 1) * sizeof(char *));
	if (!spl)
		return (write(2, "faile allocation\n", 18), NULL);
	spl[0] = ft_strdup("\0");
	if (!spl[0])
		return (write(2, "faile allocation\n", 18), NULL);
	return (spl[1] = 0, spl);//free spl
}

void	autortion(char **s, t_exp **l, int rwx)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 2;
	k = 0;
	if (s == NULL)
		return ;
	while (s[i])
	{
		if (j % 2 == 0)
		{
			ft_lstadd_back_texp(l, upgrade_input(s[i], &rwx));
			i++;
		}
		else
			ft_lstadd_back_texp(l, upgrade_input(" ", &k));
		j++;
	}
}

char	*give_arg(t_env **env, t_exp *l, char ***in)
{
	t_env	*tp;

	(*in) = (char **)malloc((1 + 1) * sizeof(char *));
	if (!(*in))
		write(2, "faile allocation\n", 18), exit(1);
	tp = (*env);
	while (tp)
	{
		if (!ft_strcmp(l->input, tp->var))
			break ;
		tp = tp->next;
	}
	return (ft_strdup(tp->value));
}

char	*s_and_r(t_exp **txp, t_env **env)
{
	t_env	*tp;
	char	*str;

	tp = (*env);
	str =  NULL;
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
		str = ft_strdup("\0");
	if (!str)
		return (write(2, "faile allocation\n", 18), NULL);
	return (str);
}
