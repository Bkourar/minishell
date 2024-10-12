#ifndef STRUCTS_H
# define STRUCTS_H

#  define bool _Bool
#  define true 1
#  define false 0

#   define ambg_1 1// ""
#   define ambg_2 2// "  val"
#   define ambg_3 3// "val  "
#   define ambg_4 4// "  val  "
#   define ambg_5 5// "val1 val2"
#   define valid 6// "val"

typedef struct s_g
{
	void	*ptr;
	struct s_g *next;
}		t_g;

typedef struct s_fd
{
	int			fd;
	struct s_fd	*next;
}		t_fd;

typedef struct s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef enum type
{
	word,
	Pipe,
	input,
	output,
	heredoc,
	append,
	d_quot,
	s_quot,
	dolar,
	err,
	L_err
}	t_p;

typedef struct s_tk
{
	char				*token;
	char				*stat;
	t_p					type;
	int				checker;
	struct s_tk	*nx;
	struct s_tk	*pv;
}						t_tk;

typedef enum s_type
{
	not_exp,
	exp
}	t_type;

typedef enum s_space
{
	not_skip,
	skip
}	t_space;

typedef enum s_state
{
	not_join,
	join
}	t_state;

typedef enum word
{
	wrd,
	not_wrd
}	t_wd;

typedef struct s_set
{
	t_type	tp;
	t_space	sp;
	t_state	st;
}			t_set;

typedef struct s_par
{
	t_type	tp;
	t_wd	wd;
	t_state	st;
}			t_par;

typedef struct s_exp
{
	char			*input;
	t_set			*set;
	int				ck;
	struct s_exp	*next;
	struct s_exp	*prv;
}					t_exp;

typedef struct s_dir
{
	char				*input;
	t_par				*par;
	int					ambg;
	int					ck;
	struct s_dir	*next;
	struct s_dir	*prv;
}					t_dir;

typedef enum tp
{
	intial,
	out,
	app,
	in,
	her_doc,
	ambiguos
}	t_e;

typedef struct s_redir
{
	t_e				tp;
	char			*file_name;
	char			*del;
	int				fd_her;
	struct s_redir	*next;
}					t_redir;

typedef struct s_sh
{
	char			**args;
	t_redir			*dir;
	struct s_sh	*next;
}					t_sh;

typedef struct s_data
{
	int	cnt;
	int	fd[2];
	int	save;
	int	std_in;
	int	std_out;
	int	*pids;
	int	i;
	int	status;
}		t_data;

#endif