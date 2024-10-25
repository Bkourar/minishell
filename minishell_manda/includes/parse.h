/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bikourar <bikourar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:56:51 by bikourar          #+#    #+#             */
/*   Updated: 2024/10/22 10:45:54 by bikourar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "minishell.h"

void	ft_lstadd_back_ttk(t_tk **lst, t_tk *new);
void	addp(int *addp, int val);
void	check_counte(int *j, int flg);
void	synatx_error(char *str);
void	synatx_quotes(char c);
void	put_error(char *str);
void	print_errors(void);
t_tk	*ft_lstnew(char *content, BOOL b);
t_tk	*create_commands(char **words);
t_tk	*pi_processing_cmd(t_tk **lst);
t_tk	*ft_lstlast(t_tk **lst);
int		pars_word(char *input, t_tk **lst);
int		process_er_1(t_tk **f, t_tk **l);
int		process_er_3(char c0, char c1);
int		check_dd(char *str, char c);
int		process_er_5(t_tk **lst);
int		process_er_2(t_tk **f);
int		process_er_4(t_tk **l);
int		check_op1(t_p i);
int		check_te(t_e i);
char	*dup_quote(char *str, int *i, char c);
char	loop(t_tk **tmp, t_p type, int *j);
char	*ck_and_dp(char c);
void	nxt(t_sh **tp);
void	ln(BOOL *bo, BOOL val);
#endif