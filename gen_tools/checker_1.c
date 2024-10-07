#include "minishell.h"

int	check_op(char c)
{
	if (!(c == '<' || c == '>' || c == '$' || c == '|' || c == '\"' || c == '\''))
		return (1);
	return (0);
}

int	check_dir(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

int	check_redir(char const *str)
{
	if (!ft_strcmp(str, "<<") || !ft_strcmp(str, ">>"))
		return (1);
	return (0);
}

int	isquote(char c)
{
	if (c == '\"' || c == '\'')
		return (1);
	return (0);
}

int	white_sp(char c)
{
	if (c == ' ' || c == '\t' || c == '\v')
		return (1);
	else if (c == '\r' || c == '\f')
		return (1);
	return (0);
}