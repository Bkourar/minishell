#ifndef TOKEN_H
# define TOKEN_H

# include "minishell.h"

int		check_redir_quote(char *str, int *i, int k);
int		check_pipe(char *str, int j, int i);
int		count_wd(char **spliting);
char	*diformer(char *str, bool *logic);
char	*restory_cmd(char *src);
void	copyin_sqoute(char *src, int *i, t_dir **lst);
void	ft_lstadd_redir(t_redir **lst, t_redir *new);
void	ft_lstadd_back_msh(t_sh **lst, t_sh *new);
void	std_copy(char *src, int *i, t_dir **lst);
void	pars_whit_sq(char *src, int *i, t_dir **lst);
void	copy_std_n(char *src, int *i, t_dir **lst);
t_sh	*token_data(char *str, t_env *env , t_sh **head);
t_sh	*pi_processing_in(char *str, t_sh **node, t_env **env);
t_sh	*creat_commandline(t_sh **node, char *str, int *i);
t_redir	*creat_node(char *str, t_redir *node, t_env **env);
t_dir	*set_data(char *in, t_dir **lst);
void	pi_processing_here(int	fd, char *dilemiter, t_env **env, bool *b);
char	*join_arg(char **spl);
int		ft_lstsize(t_sh *lst);
int		check_pd(char c);
char	**double_arr(t_tk **l);
char	**token_input(char *in, t_tk **lst);
int		failing(t_tk *l, void *arg, bool flg);
int	    check_pd(char c);
int	    strnlcpy(char **dst, unsigned int *j,char *src, char c);
int 	check_in_quote(char *inf, char c);
#endif