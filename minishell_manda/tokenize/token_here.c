/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_here.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bikourar <bikourar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:23:31 by bikourar          #+#    #+#             */
/*   Updated: 2024/10/24 23:20:48 by bikourar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parse_here(char *src, int *i, t_dir **head)
{
	if (src[*i] && src[*i] == '\"')
		*i += 1;
	while (src[*i] && src[*i] != '\"')
	{
		if (src[*i] == '\'')
			pars_whit_sq(src, i, head);
		else
			copy_std_n(src, i, head);
		if (failed(*head, NULL, FALSE))
			return ;
	}
	if (src[*i] && src[*i] == '\"')
		i += 1;
}

static t_dir	*setup_list(char **in, t_dir **lst, BOOL *l)
{
	t_dir	*head;
	int		i;
	int		j;

	i = 0;
	head = NULL;
	while (in[i])
	{
		j = 0;
		if (in[i][0] == '\"')
			(parse_here(in[i], &j, &head), ln(l, TRUE));
		else if (in[i][0] == '\'')
			(cin_singlq(in[i], &j, &head), ln(l, TRUE));
		else
			copy_gen(in[i], &j, &head);
		if (failed(*lst, NULL, FALSE))
			return (NULL);
		i++;
	}
	(*lst) = head;
	return ((*lst));
}

static char	*concatition_inf(t_dir **lst)
{
	t_dir	*nd1;
	char	*str;
	int		i;

	str = NULL;
	nd1 = (*lst);
	i = 0;
	while (nd1)
	{
		if (nd1->par->st == join)
			i++;
		str = ft_strjoin(str, nd1->input);
		if (!str)
			return (write(2, "faile allocation\n", 18), NULL);
		nd1 = nd1->next;
	}
	return (str);
}

char	*diformer(char *str, BOOL *logic)
{
	t_dir	*head;
	char	**spl;
	char	*correct;

	head = NULL;
	if (check_empty(str))
		return (*logic = TRUE, ft_strdup("\0"));
	head = set_data(str, &head);
	if (!head)
		return (NULL);
	spl = mise_ajour_input(&head);
	if (!spl)
		return (NULL);
	head = setup_list(spl, &head, logic);
	if (!head)
		return (NULL);
	correct = concatition_inf(&head);
	if (!correct)
		return (NULL);
	return (correct);
}
