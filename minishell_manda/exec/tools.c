/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkacimi <abkacimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:30:08 by abkacimi          #+#    #+#             */
/*   Updated: 2024/10/22 21:17:48 by abkacimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	just_cmd(char *arg)
{
	int	i;

	i = 0;
	while (arg && arg[i])
	{
		if (arg[i] == '/')
			return (0);
		i++;
	}
	return (1);
}

char	*exec_join(char const *s1, char const *s2)
{
	char	*string;
	int		i;
	int		j;

	j = 0;
	if (!s1 && !s2)
		return (string = NULL, NULL);
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	string = (char *)ft_allocate(1, ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!string)
		return (NULL);
	i = 0;
	while (s1[i])
		string[j++] = s1[i++];
	i = 0;
	while (s2[i])
		string[j++] = s2[i++];
	string[j] = '\0';
	return (string);
}

char	*get_path(char **arr, char *cmd)
{
	int		i;
	char	*pth;

	i = 0;
	pth = NULL;
	if (just_cmd(cmd) == 0)
	{
		if (access(cmd, X_OK) != -1)
			return (cmd);
		return (NULL);
	}
	while (arr && arr[i])
	{
		pth = exec_join(arr[i], "/");
		pth = exec_join(pth, cmd);
		if (access(pth, X_OK) != -1)
			return (pth);
		i++;
		pth = NULL;
	}
	pth = NULL;
	return (NULL);
}

char	*ft_save_pth(int flag)
{
	static char	home[PATH_MAX];

	if (flag == 1)
	{
		getcwd(home, PATH_MAX);
	}
	return (home);
}
