/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bikourar <bikourar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:29:36 by bikourar          #+#    #+#             */
/*   Updated: 2024/10/25 16:51:16 by bikourar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check(long number)
{
	long	i;
	int		j;

	i = 1;
	j = 0;
	if (number <= 0)
	{
		if (number < 0)
			number *= -1;
		j++;
	}
	while (number / i > 0)
	{
		i *= 10;
		j++;
	}
	return (j);
}

static char	*dynamic(long number, int j)
{
	char	*str;

	str = (char *)ft_allocate(1, sizeof(char) * (j + 1));
	if (!str)
		return (NULL);
	str[j--] = '\0';
	if (number <= 0)
	{
		if (number < 0)
		{
			str[0] = '-';
			number = -number;
		}
		else
			str[j--] = '0';
	}
	while (number)
	{
		str[j--] = (number % 10) + '0';
		number /= 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	long	nbr;
	int		i;

	nbr = (long)n;
	i = check(nbr);
	return (dynamic(nbr, i));
}

BOOL	ischild(int flg, BOOL logic)
{
	static BOOL	b;

	if (flg == 1)
		b = logic;
	return (b);
}

int	vld(char *s, int p, int i, int j)
{
	if (s[i] == '\0')
		return (0);
	if (s_q(s[i]))
	{
		while (s[i] && j != 2)
		{
			if (s_q(s[i]))
				j++;
			i++;
		}
		if (s[i] == s[p + 1])
			return (1);
	}
	else if (d_q(s[i]))
	{
		while (s[i] && j != 2)
		{
			if (s_q(s[i]))
				j++;
			i++;
		}
		if (s[i] == s[p + 1])
			return (1);
	}
	return (vld(s, p, i + 1, 0));
}
