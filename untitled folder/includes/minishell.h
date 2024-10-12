#ifndef MINISHELL_H
# define MINISHELL_H

# include "structs.h"
# include <signal.h>
# include "signal.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <ctype.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <termios.h>
# include "parse.h"
# include "token.h"
# include "expanse.h"
# include "execute.h"
# include <readline/readline.h>
# include <readline/history.h>

int		replace_space(char *dst, int *i, char *src);
int		ft_strcmp(char const *s1, char const *s2);
int		count_word(char const *string, char c);
int		check_redir(char const *str);
int		count_wd(char **spliting);
int		check_dir(char c);
int		check_op(char c);
int		white_sp(char c);
int		isquote(char c);
char	*ft_strncpy(char *dst, char *src, int index);
char	*ft_strjoin(char const *s1, char const *s2);
char	*f_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
char	*ft_strdup(char const *src);
size_t	ft_strlen(const char *theString);
char	*ft_itoa(int n);
int		check_dolar(char *str);
int		check_space(char *str);
int		ft_lstsize_tk(t_tk *lst);
int		strnlcpy(char **dst, unsigned int *j, char *src, char c);
#endif