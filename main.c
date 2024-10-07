#include "minishell.h"

static int mt_or_only_sp(char *str)
{
	if (!str || str[0] == '\0')
		return (3);
	while(*str)
	{
		if (!white_sp(*str))
			return (22);
		str++;
	}
	return (3);
}

static t_tk	*parse_line(char *line)
{
	char	**shell_line;
	t_tk	*tok;

	tok = NULL;
	shell_line = NULL;
	if ((mt_or_only_sp(line)) == 3)
		return (NULL);
	shell_line = token_input(line, &tok);
	if (!shell_line)
		return (NULL);
	tok = create_commands(shell_line);
	if (!tok)
		return (write(2, "fail allocation\n", 17), NULL);
	tok = pi_processing_cmd(&tok);
	if (!tok)
		return (NULL);
	return (tok);
}

static void	main_loop(t_env **en_v, t_sh **cmd, t_tk **prs)
{
	char	*readit;
	struct termios termios;

	ft_signal();
	tcgetattr(STDIN_FILENO, &termios); 
	while (1)
	{
		rl_catch_signals = 0;
		tcsetattr(STDIN_FILENO, TCSANOW, &termios);
		readit = readline("bash-1.1$ ");
		if (!readit)
			break ;
		add_history(readit);
		(*prs) = parse_line(readit);
		if (!(*prs))
			continue ;
		(*cmd) = token_data(readit, *en_v, cmd);
		if (!(*cmd))
			continue ;
		(ft_start_exec(cmd, en_v));
		free(readit);
	}
}

int main(int ac, char **av, char **env)
{
	t_tk	*prs;
	t_sh	*cmd;
	t_env	*en_v;

	cmd = NULL;
	(void)ac;
	(void)av;
	en_v = parse_env(env);
	main_loop(&en_v, &cmd, &prs);
	write(2, "exit\n", 6);
}

