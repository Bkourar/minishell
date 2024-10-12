#ifndef PARSE_H
# define PARSE_H

# include "minishell.h"

void	ft_lstadd_back_ttk(t_tk **lst, t_tk *new);
void	complete_type(t_tk **lst, int type);
void	counter(int *counter, int val);
void	synatx_error(char *str);
void	synatx_quotes(char c);
void	put_error(char *str);
void	print_errors();
t_tk	*create_commands(char **words);
t_tk	*pi_processing_cmd(t_tk **lst);
t_tk	*ft_lstnew(char *content, bool b);
t_tk	*ft_lstlast(t_tk **lst);
int		pars_word(char *input, t_tk **l, int i, int j);
int		pi_processing_err_1(t_tk **f, t_tk **l);
int		pi_processing_err_3(char c0, char c1);
int		checker_typing(char const *santax);
int		pi_processing_err_5(t_tk **lst);
int		pi_processing_err_2(t_tk **f);
int		pi_processing_err_4(t_tk **l);
int		check_op1(t_p i);
char	*dup_quote(char *str, int *i, char c);
char	*ck_and_dp(char c);
char	loop(t_tk **tmp, t_p type, int *j);
int		check_dd(char *str, char c);
void	check_counte(int *j, int flg);
// void	//free_arr(char **arg);
// void	//free_tok(t_tk **l);
#endif