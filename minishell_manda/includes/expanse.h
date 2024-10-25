/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanse.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bikourar <bikourar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 18:17:11 by bikourar          #+#    #+#             */
/*   Updated: 2024/10/22 15:03:06 by bikourar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSE_H
# define EXPANSE_H

# include "minishell.h"

char	*process_dr(char *in, t_env **env, t_redir *d, int *i);
char	*search_in_eva(t_dir *nd, t_env **ev);
char	**mise_ajour_input(t_dir **lst);
void	copy_whit_singlq(char *src, int *i, t_dir **lst);
void	copy_whit_doublq(char *src, int *i, t_dir **lst);
void	o_p(int *chmod, int tp, int wd, int st);
void	copy_in_sqoute(char *src, int *i, t_dir **lst);
void	copy_std_norm(char *src, int *i, t_dir **lst);
void	expand_wqoute(char *arr, int *i, t_dir **lst);
void	copy_expanse(char *src, int *i, t_dir **lst);
void	copy_singleq(char *src, int *i, t_dir **lst);
void	copy_std_dfl(char *src, int *i, t_dir **lst);
void	add_dir(t_dir **lst, t_dir *new);
void	parsse_wesq(char *src, int *i, t_dir **lst);
void	cin_singlq(char *src, int *i, t_dir **lst);
void	expand_dir(char *arr, int *i, t_dir **lst);
void	copy_gen(char *src, int *i, t_dir **lst);
void	put_ambeg(char *str);
void	copy_input(char *src, int *i, t_exp **lst);
void	copy_whit_sq(char *src, int *i, t_exp **lst);
void	copy_whit_dq(char *src, int *i, t_exp **lst);
void	copy_standard(char *src, int *i, t_exp **lst, BOOL b);
void	skip_wspace(char *str, int *j, t_exp **lst);
void	upgrade_setting(t_set **setting, int rwx);
void	p_attr(int *chmod, int tp, int sp, int st);
void	ad_bk_exp(t_exp **lst, t_exp *new);
void	copy_general(char *src, int *i, t_exp **lst);
void	cin_singl_q(char *src, int *i, t_exp **lst);
void	parssing_expand(char *src, int *i, t_exp **head);
void	expand(char *arr, int *i, t_exp **lst);
void	copy_std(char *src, int *i, t_exp **lst);
void	parsse_sq(char *src, int *i, t_exp **lst);
void	expand_sq(char *arr, int *i, t_exp **lst);
void	copy_in_sq(char *src, int *i, t_exp **lst);
void	autortion(char **s, t_exp **l, int rwx, BOOL *b);
void	copy_status(char *in, int *j, t_exp **l);
void	copy_single_q(char *src, int *i, t_exp **lst);
void	give_status(char *arr, int *i, t_exp **lst, BOOL b);
void	change(t_redir **hd, BOOL b);
int		open_here(char *del, t_env **env, char *c, BOOL *b);
int		check_error_ambiguous(t_dir *n, t_dir **head);
int		failed(t_dir *l, void *arg, BOOL flg);
int		faile(t_exp *l, void *arg, BOOL flg);
int		ambiguous_redirect(t_redir **hd);
int		valid_condtion(char *str, int p);
int		own_exp(int tp, int sp, int st);
int		condition_for_split(t_exp **hd);
int		lstsiz_exp(t_exp *lst);
int		lstsiz_dr(t_dir *lst);
int		check_equal(char *str);
int		valid_join(t_exp *nd);
int		check_empty(char *s);
int		valid_expand(char c);
int		is_nbr(char c);
int		is_alpha(char c);
int		check_hrd(char *s, int p);
t_dir	*up_redire(char *in, int *chmod, int j);
t_dir	*check_ambiguous_redirect(t_dir **l, char *i, t_redir **d);
t_dir	*config_redirect(char *in, int j, t_dir *nd);
t_dir	*analyse_case_ambg(t_dir *tp, t_env **ev);
t_dir	*analyse_input(char *in, t_dir **lst, int *i);
t_dir	*upgrade_list(char **in, t_dir **lst);
t_exp	*update_input(char *in, t_exp **lst, BOOL b);
t_exp	*config(char *in);
t_exp	*upgrade_input(char *in, int *chmod);
t_exp	*ft_lstlast_exp(t_exp **lst);
t_exp	*update_list(char **in, t_exp **lst, BOOL b, int j);
char	**pi_processing_expand(char *str, t_env **env, BOOL b);
char	**parse_value(t_exp **hd, t_env **env, BOOL *b);
char	*give_arg(t_env **env, t_exp *l, char ***in);
char	**update_array(t_exp **lst, int i);
char	*s_and_r(t_exp **txp, t_env **env);
void	get_hard_cd(char *s, int *i, t_exp **l);
#endif