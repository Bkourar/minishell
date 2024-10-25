/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_help.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkacimi <abkacimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:29:57 by abkacimi          #+#    #+#             */
/*   Updated: 2024/10/13 15:29:57 by abkacimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*new_j(char const *s1, char const *s2);
char	*ft_sdup_ex(char const *src);

char	*new_j(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	j = 0;
	if (s1 == NULL && s2 == NULL)
		return (str = NULL, NULL);
	else if (s1 == NULL)
		return ((char *)gc_env(1, ft_strlen(s2) + 1));
	else if (s2 == NULL)
		return ((char *)gc_env(1, ft_strlen(s1) + 1));
	str = (char *)gc_env(1, ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (exit(1), NULL);
	i = 0;
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = '\0';
	return (str);
}

char	*ft_sdup_ex(char const *src)
{
	char	*dst;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (src == NULL)
		return (NULL);
	dst = (char *)gc_env(1, sizeof(char) * (ft_strlen(src) + 1));
	if (!dst)
		return (write(2, "faile allocation\n", 18), NULL);
	while (src[i])
		dst[j++] = src[i++];
	dst[j] = '\0';
	return (dst);
}
