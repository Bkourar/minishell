#ifndef EXPANSE_H
# define EXPANSE_H

# include "minishell.h"

char	*pi_processing_redirect(char *in, t_env **env, t_redir *d);
char	*search_in_eva(t_dir *nd, t_env **ev);
char	**mise_ajour_input(t_dir **lst);
void	copy_whit_singlq(char *src, int *i, t_dir **lst);
void	copy_whit_doublq(char *src, int *i, t_dir **lst);
void	owner_premt(int *chmod, int	tp, int	wd, int	st);
void	copy_in_sqoute(char *src, int *i, t_dir **lst);
void	copy_std_norm(char *src, int *i, t_dir **lst);
void	expand_wqoute(char *arr, int *i, t_dir **lst);
void	copy_expanse(char *src, int *i, t_dir **lst);
void	copy_singleq(char *src, int *i, t_dir **lst);
void	copy_std_dfl(char *src, int *i, t_dir **lst);
void	ft_lstadd_back_dir(t_dir **lst, t_dir *new);
void	parsse_wesq(char *src, int *i, t_dir **lst);
void	cin_singlq(char *src, int *i, t_dir **lst);
void	expand_dir(char *arr, int *i, t_dir **lst);
void	copy_gen(char *src, int *i, t_dir **lst);
void	put_ambeg(char *str);
int		open_here(char *del, t_env **env, char *c, bool *b);
int		failed(t_dir *l, void *arg, bool flg);
int		ambiguous_redirect(t_redir **hd);
int		valid_condtion(char *str, int p);
int		ft_lstsiz_dir(t_dir *lst);
int		check_empty(char *s);
int		valid_expand(char c);
int		is_numeric(char c);
int		is_alpha(char c);
t_dir	*upgrade_redirect(char *in, int *chmod, int j);
t_dir	*check_ambiguous_redirect(t_dir **l, char *in);
t_dir	*config_redirect(char *in, int j, t_dir *nd);
t_dir	*analyse_case_ambg(t_dir *tp, t_env **ev);
t_dir	*analyse_input(char *in, t_dir **lst);
t_dir	*upgrade_list(char **in, t_dir **lst);
void	copy_status(char *in, int *j, t_exp **l);
//------------------------------------------------------------------------------------------//
t_exp	*update_input(char *in, t_exp **lst);
t_exp	*config(char *in);
t_exp	*upgrade_input(char *in, int *chmod);
t_exp	*ft_lstlast_exp(t_exp **lst);
t_exp	*update_list(char **in, t_exp **lst);
void	copy_input(char *src, int *i, t_exp **lst);
void	copy_whit_sq(char *src, int *i, t_exp **lst);
void	copy_whit_dq(char *src, int *i, t_exp **lst);
void	copy_standard(char *src, int *i, t_exp **lst);
void	skip_wspace(char *str, int *j, t_exp **lst);
void	upgrade_setting(t_set **setting, int rwx);
void	premission(int *chmod, int tp, int sp, int st);
void	ft_lstadd_back_texp(t_exp **lst, t_exp *new);
void	copy_general(char *src, int *i, t_exp **lst);
void	cin_singl_q(char *src, int *i, t_exp **lst);
void	parssing_expand(char *src, int *i, t_exp **head);
void	expand(char *arr, int *i, t_exp **lst);
void	copy_std(char *src, int *i, t_exp **lst);
void	parsse_sq(char *src, int *i, t_exp **lst);
void	expand_sq(char *arr, int *i, t_exp **lst);
void	copy_in_sq(char *src, int *i, t_exp **lst);
void	autortion(char **s, t_exp **l, int rwx);
int		faile(t_exp *l, void *arg, bool flg);
int		own_exp(int tp, int sp, int st);
int		condition_for_split(t_exp **hd);
int		ft_lstsize_exp(t_exp *lst);
int		check_equal(char *str);
char	**pi_processing_expand(char *str, t_env **env);
char	**parse_value(t_exp **hd, t_env **env);
char	**update_array(t_exp **lst, int i);
char	*give_arg(t_env **env, t_exp *l, char ***in);
char	*s_and_r(t_exp **txp, t_env **env);
int		valid_join(t_exp *nd);
void	copy_single_q(char *src, int *i, t_exp **lst);
void	give_status(char *arr, int *i, t_exp **lst, bool b);
#endif