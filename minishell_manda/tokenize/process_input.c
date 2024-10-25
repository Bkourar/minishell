/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bikourar <bikourar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:23:18 by bikourar          #+#    #+#             */
/*   Updated: 2024/10/25 16:54:08 by bikourar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_arg(char **spl)
{
	char	*str;
	int		i;

	i = 0;
	str = NULL;
	while (spl[i])
	{
		str = ft_strjoin(str, spl[i]);
		if (!str)
			return (write(2, "allocation faile222\n", 21), NULL);
		i++;
	}
	return (str);
}

static int	check_magi(char *s, int p)
{
	if (p != 0 && (is_alpha(s[p - 1]) || s[p - 1] == 61))
		return (0);
	if (d_q(s[p]) && d_q(s[p + 1]) && s[p + 2] == '\0')
		return (1);
	else if (s_q(s[p]) && s_q(s[p + 1]) && s[p + 2] == '\0')
		return (1);
	else if (d_q(s[p]) && d_q(s[p + 1]) && w_sp(s[p + 2]) && vld(s, p, 0, 0))
		return (1);
	else if (s_q(s[p]) && s_q(s[p + 1]) && w_sp(s[p + 2]) && vld(s, p, 0, 0))
		return (1);
	return (0);
}

static void	rm_q(char *s)
{
	int	check;
	int	i;

	i = 0;
	while (s[i])
	{
		check = check_magi(s, i);
		if (check == 1)
		{
			s[i++] = (char)(-15708);
			s[i++] = (char)(-15708);
		}
		else
			i++;
	}
}

t_sh	*pi_processing_in(char *str, t_sh **node, t_env **env, int i)
{
	char	**cmd;
	t_sh	*new;

	new = (t_sh *) ft_allocate(1, sizeof(t_sh));
	if (!new)
		return (NULL);
	((rm_q(str)), cmd = pi_processing_expand(str, env, TRUE));
	if (!cmd)
		return (NULL);
	new->args = (char **)ft_allocate(1, sizeof(char *) * (count_wd(cmd) + 1));
	if (!new->args)
		return (NULL);
	while (cmd[i])
	{
		if (cmd[i][0] == (char)(-62) || e_s(cmd[i][1]))
			new = creat_cmdline(&new, ft_strdup("\0"), &i);
		else
			new = creat_cmdline(&new, cmd[i], &i);
		i++;
	}
	new->args[i] = 0;
	return (new->dir = (*node)->dir, new->next = NULL, new);
}

int	old(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$')
			j++;
		i++;
	}
	if (j % 2 == 0)
		return (0);
	return (1);
}
