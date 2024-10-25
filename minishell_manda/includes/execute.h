/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abkacimi <abkacimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:30:42 by abkacimi          #+#    #+#             */
/*   Updated: 2024/10/22 19:24:50 by abkacimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"

/*################   exec   ################*/
void		ft_start_exec(t_sh **cmd, t_env **env);
void		main_exec(t_data *dt, t_sh *cmd, t_env *env, char **path);
void		deal_with_pp(t_data *dt, t_sh *cmd);
void		ft_fnsh(t_data *dt);
void		ft_restorefds(t_data *dt);
void		execute_builtin(t_sh *cmd, t_env *env);
int			its_bult(char *cmd);
void		handle_redirections(t_redir *redirections, int flag);
void		ft_spcl_red(int flag);
void		build_echo(char **args, int i);
void		ft_pwd(void);
void		ft_unset(t_sh *cmd, t_env *env);
void		ft_exit(t_sh *cmd);
void		build_export(t_sh *cmd, t_env *env);
void		ft_set_it(t_env *env, const char *var, const char *new_value);
char		*ft_get_cwd(void);
void		change_directory(t_sh *cmd, t_env *env);
int			ft_hrb(int flag, int stt);
int			just_cmd(char *arg);

/*################   env   ################*/
t_env		*parse_env(char **envir);
void		ft_show_env(t_env *env);
char		**env_to_arr(t_env *env, int i);
char		**environnement_pth(t_env *e);
char		*get_path(char **arr, char *cmd);
void		ft_del_one(t_env *head, const char *var);
t_env		*env_lstnew(const char *var, const char *value);
void		env_lst_back(t_env **lst, t_env *new);
char		*get_value_e(t_env *env, char *var);
char		*ft_save_pth(int flag);

/*################   more   ################*/
int			ft_isalpha(char c);
int			ft_isalnum(char c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
char		*ft_strchr(const char *s, int c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*exec_join(char const *s1, char const *s2);
char		*new_j(const char *s1, const char *s2);
char		**ft_ex_splt(char const *s, char c);
char		*ft_sdup_ex(char const *src);
long long	atoll_x(char *str);
void		ft_putstr_x(char *s1, char *s2, char *s3, int fd);
void		ft_perror(char *str, int st);
void		show_prblm(char *file, int prblm, int flag);

void		*ft_allocate(int flag, int size);
void		fd_collector(int flag, int fd);
void		*gc_env(int flag, int size);

#endif