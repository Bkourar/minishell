#include "minishell.h"

// static void	free_tk(t_tk **k)
// {
// 	t_tk	*tp1;
// 	t_tk	*tp2;

// 	tp1 = (*k);
// 	tp2 = tp1->nx;
// 	while (tp2)
// 	{
// 		free(tp1->token);
// 		free(tp1);
// 		tp1 = tp2;
// 		tp2 = tp2->nx;
// 	}
// 	free(tp1->token);
// 	free(tp1);
// }

char	**double_arr(t_tk **l)
{
	t_tk	*tp;
	char	**s;
	int		i;

	s = (char **)malloc((ft_lstsize_tk((*l)) + 1) * sizeof(char *));
	if (!s)
		return (write(2, "faile allocation\n", 18), NULL);
	tp = (*l);
	i = 0;
	while (tp)
	{
		s[i++] = ft_strdup(tp->token);
		if (!s[i - 1])
			return (write(2, "faile allocation\n", 18), NULL);
		tp = tp->nx;
	}
	s[i] = 0;
	return (s);
}

int	check_pipe(char *str, int j, int i)
{
	int		counter;
	char	c;

	counter = 0;
	while (str[i])
	{
		if (isquote(str[i]) && counter == 0)
		{
			c = str[i];
			counter++;
			i++;
			while (str[i] && str[i] != c)
			{
				if (i == j)
					return (1);
				i++;
			}
			if (str[i] && str[i] == c)
				counter++;
		}
		if (counter == 2)
			counter = 0;
		i++;
	}
	return (0);
}
