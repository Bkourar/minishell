/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bikourar <bikourar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:32:39 by bikourar          #+#    #+#             */
/*   Updated: 2024/10/24 20:05:36 by bikourar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "minishell.h"

int		pi_processing_here(int fd, char *dilemiter, t_env **env, BOOL *b);
int		check_redir_quote(char *str, int *i, int k);
int		failing(t_tk *l, void *arg, BOOL flg);
int		check_pipe(char *str, int j, int i);
char	*diformer(char *str, BOOL *logic);
int		ft_lstsize(t_sh *lst);
int		skp_w_sp(char *in);
int		check_pd(char c);
int		check_pd(char c);
char	*restory_cmd(char *src);
void	change_and_rpl(char *str, char *stack, int i);
void	copyin_sqoute(char *src, int *i, t_dir **lst);
void	ft_lstadd_redir(t_redir **lst, t_redir *new);
void	pars_whit_sq(char *src, int *i, t_dir **lst);
void	copy_std_n(char *src, int *i, t_dir **lst);
void	ft_lstadd_back_msh(t_sh **lst, t_sh *new);
void	check_in_quote(char *inf, char c, int *i);
void	std_copy(char *src, int *i, t_dir **lst);
void	check_exit(t_sh **l);
void	chos(t_e *i, int j);
char	**token_input(char *in, t_tk **lst);
char	**double_arr(t_tk **l);
char	*join_arg(char **spl);
t_sh	*pi_processing_in(char *str, t_sh **node, t_env **env, int i);
t_sh	*creat_cmdline(t_sh **node, char *str, int *i);
t_sh	*token_data(char *str, t_env *env, t_sh **hd);
t_redir	*creat_node(char *str, t_redir **nd, t_env **env);
t_dir	*set_data(char *in, t_dir **lst);
int		check_magic(char *s, t_exp *l);
int		old(char *str);
void	copy_empty(char *s, int *i, t_exp **l, BOOL b);
#endif