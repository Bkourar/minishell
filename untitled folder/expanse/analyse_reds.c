#include "minishell.h"

static char	*concatition_dir(t_dir **lst)
{
	t_dir	*nd1;
	char	*str;

	str = NULL;
	if ((*lst) == NULL)
		return (str);
	nd1 = (*lst);
	while (nd1)
	{
		str = ft_strjoin(str, nd1->input);
		if (!str)
			return (write(2, "faile allocation\n", 18), NULL);
		nd1 = nd1->next;
	}
	return (str);
}

int	check_empty(char *s)
{
	if (s == NULL)
		return (0);
	if (s[0] == '\"' && s[1] == '\"' && s[2] == '\0')
		return (1);
	else if (s[0] == '\'' && s[1] == '\'' && s[2] == '\0')
		return (1);
	return (0);
}

char	*pi_processing_redirect(char *in, t_env **env, t_redir *d, int *i)
{
	t_dir	*head;
	char	*correct;

	head = NULL;
	if (d != NULL && d->tp == her_doc)
		return (ft_strdup(&in[*i]));
	if (check_empty(in))
		return (ft_strdup("\0"));
	head = analyse_input(in, &head, i);
	if (!head)
		return (NULL);
	head = upgrade_list(mise_ajour_input(&head), &head);
	if (!head)
		return (NULL);
	head = analyse_case_ambg(head, env);
	head = check_ambiguous_redirect(&head, &in[*i], &d);
	if (head == NULL)
		return (NULL);
	correct = concatition_dir(&head);
	if (!correct)
		return (NULL);
	return (correct);
}

void	give_status(char *arr, int *i, t_exp **lst, bool b)
{
	char	*dst;
	int		chmod;

	dst = NULL;
	chmod = 0;
	if (b == true && !ft_strcmp(arr, "$?"))
	{
		dst = ft_itoa(ft_hrb(0, 0));
		(premission(&chmod, 0, 0, 0));
		
	}
	else if (b == false && arr[*i] == '$' && arr[(*i + 1)] == '?')
	{
		dst = ft_itoa(ft_hrb(0, 0));
		(premission(&chmod, 0, 2, 1));
	}
	if (faile((*lst), dst, true))
		return ;
	*i += 2;
	(ft_lstadd_back_texp(lst, upgrade_input(dst, &chmod)));
}