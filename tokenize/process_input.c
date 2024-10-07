#include "minishell.h"

int	count_wd(char **spliting)
{
	int	i;

	i = 0;
	if (!spliting)
		return (0);
	while (spliting[i])
		i++;
	return (i);
}

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
			return (write(2, "allocation faile\n", 18), NULL);
		i++;
	}
	return (str);
}

t_sh	*pi_processing_in(char *str, t_sh **node, t_env **env)
{
	char		**cmd;
	t_sh		*new;
	int			i;

	(void)env;
	new = (t_sh *) malloc(sizeof(t_sh));
	if (!new)
		return (NULL);
	cmd = pi_processing_expand(str, env);
	if (!cmd)
		return (NULL);
	i = 0;
	new->args = (char **)malloc(sizeof(char *) * (count_wd(cmd) + 1));
	if (!new->args)
		return (NULL);
	while (cmd[i])
	{
		new = creat_commandline(&new, cmd[i], &i);
		i++;
	}
	new->args[i] = 0;
	return (new->dir = (*node)->dir, new->next = NULL, new);
}
