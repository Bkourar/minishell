NAME := minishell
SRCS1 := $(addprefix parse/, lexic_cmd.c lexic_wrd.c tools_parse.c checker_pars.c \
		analyse_cmd.c processe_parse.c santax_err.c)
SRCS2 := $(addprefix gen_tools/, tools1.c split.c checker_1.c checker_2.c itoa.c \
		tools2.c)
SRCS3 := $(addprefix tokenize/, tools_tk.c tokenisation.c checker_tk.c tools_list.c \
		process_input.c process_here.c token_here.c tools_here.c token_input.c tools_tk_in.c)
SRCS4 := $(addprefix expanse/, analyse_ambg.c checker.c tool1_process_reds.c tools_reds.c \
		tool2_process_reds.c analyse_reds.c process_reds.c tlist_reds.c process_here.c checker_exp.c \
		process_expand.c analyse_expand.c parsing_expand.c tlist_expand.c tools_expand.c tools1_expand.c \
		tools2_expand.c )
SRCS5 := $(addprefix exec/, env.c env_tools.c tools.c tools1.c tools2.c tools3.c g_collect.c bultins.c \
		change_dir.c echo.c exec_tools.c execution.c  exit_it.c  export.c pwd.c redir.c unset.c x_splt.c \
		gc_help.c fd_collect.c gc_env.c redir_tools.c)
SRCS6 := $(addprefix signal/, pi_process_chaild.c pi_process_signal.c)

INC := includes
DIR := object/
RED = \033[0;31m
GREEN = \033[0;32m
CO = \033[0;37m
BLUE = \033[0;36m

CC = cc
CFLAGS = -Wall -Werror -Wextra
OBJS = $(addprefix $(DIR), $(SRCS:%.c=%.o))
SRCS = $(SRCS1) $(SRCS2) $(SRCS3) $(SRCS4) $(SRCS5) $(SRCS6) main.c

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline
	@echo "\n$(BLUE) loading [...................... 100%] $(CO)MAKED bash"

$(DIR)%.o: %.c $(INC)/minishell.h
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c -I$(INC) $< -o $@
	@echo "$(GREEN)build_....._$(CO)$@"

clean:
	@rm -rf $(DIR)
	@echo "\n$(RED)..........100% CLEANED $(CO)bash"

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
