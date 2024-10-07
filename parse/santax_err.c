#include "minishell.h"

void	put_error(char *str)
{
	int	i;

	i = 0;
	write(1, "`", 1);
	while (str[i])
		write(2, &str[i++], 1);
	write(2, "'\n", 2);
}

void	synatx_error(char *str)
{
	write(2, "bash: syntax error near", 24);
	write(2, " unexpected token ", 19);
	put_error(str);
	ft_hrb(1, 258);
}

void	print_errors()
{
	write(2, "bash: syntax error near ", 25);
	write(2, "unexpected token `newline'\n", 28);
	ft_hrb(1, 258);
}


void	synatx_quotes(char c)
{
	write(2, "bash: unexpected EOF while", 27);
	write(2, " looking for matching `", 24);
	write(2, &c, 1);
	write(2, "'\n", 2);
	ft_hrb(1, 258);
}

void	put_ambeg(char *str)
{
	write(2, "bash : ", 8);
	write(2, str, ft_strlen(str));
	write(2, ": ambiguous redirect\n", 22);
	ft_hrb(1, 1);
}