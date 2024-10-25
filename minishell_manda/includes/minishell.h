/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bikourar <bikourar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:16:28 by abkacimi          #+#    #+#             */
/*   Updated: 2024/10/25 16:54:08 by bikourar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <ctype.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <termios.h>
# include "structs.h"
# include "signal.h"
# include "parse.h"
# include "expanse.h"
# include "token.h"
# include "execute.h"
# include <readline/readline.h>
# include <readline/history.h>

int		g_sig_heredoc;

int		replace_space(char *dst, int *i, char *src);
int		ft_strcmp(char const *s1, char const *s2);
int		count_word(char const *string, char c);
int		check_redir(char const *str);
int		count_wd(char **spliting);
int		check_dir(char c);
int		check_op(char c);
int		w_sp(char c);
int		isquote(char c);
char	*ft_strncpy(char *dst, char *src, int index);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
char	*ft_strdup(char const *src);
size_t	ft_strlen(const char *theString);
char	*ft_itoa(int n);
int		check_dolar(char *str);
int		check_space(char *str);
int		ft_lstsize_tk(t_tk *lst);
BOOL	ischild(int flg, BOOL logic);
t_sh	*lstlast_tsh(t_sh **lst);
void	*cmt(t_sh *cm, int i);
t_redir	*ltdr(t_redir **lst);
int		strnlcpy(char **dst, unsigned int *j, char *src, char c);
int		vld(char *s, int p, int i, int j);
int		d_q(char c);
int		s_q(char c);
int		e_s(char c);
#endif