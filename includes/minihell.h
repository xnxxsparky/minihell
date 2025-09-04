/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minihell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcausseq <bcausseq@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 03:04:29 by bcausseq          #+#    #+#             */
/*   Updated: 2025/09/05 01:23:14 by bcausseq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIHELL_H
# define MINIHELL_H
# define FAILURE				2
# define ITALIC					"\033[3m"
# define RED					"\033[31m"
# define BOLD					"\033[1m"
# define GREEN					"\033[32m"
# define YELLOW					"\033[33m"
# define CYAN					"\033[34m"
# define MAGENTA				"\033[35m"
# define GRAY					"\033[90m"
# define RESET					"\033[0m"
# define RL_START_IGNORE		"\001"
# define RL_END_IGNORE			"\002"
# define MS_PARSER_ERR			1
# define MS_PARSER_OKK			0
# define READ_SIDE				0
# define WRITE_SIDE				1
# define CYAN_IGNORED			"\001\033[34m\002"
# define RESET_IGNORED			"\001\033[0m\002"
# define MAGENTA_IGNORED		"\001\033[35m\002"

# include <stdbool.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <curses.h>
# include <term.h>
# include <fcntl.h>
# include <errno.h>
# include "lexer.h"

extern volatile sig_atomic_t	g_sig;

typedef struct s_cmd
{
	char	**cmd;
	char	*path;
	char	*name_fd_in;
	char	*name_fd_out;
	int		fd_in;
	int		fd_out;
}	t_cmd;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	t_env		*env;
	char		**env_ar;
	t_cmd		*cmd_dec;
	t_token		*cmd;
	char		*prompt;
	char		*cmd_user;
	int			retcode;
	int			*pids;
}	t_shell;

typedef void					(*t_op_function)(t_shell *shel, int index);

typedef struct s_op
{
	char			*name;
	t_op_function	func;
}	t_op;

//env_manager.c
t_env
*env_finder(t_env *env, char *name);

t_env
*env_instantiate(char **env);

//env_utils.c
t_env
*env_lstnew(char *name, char *value);

t_env
**env_addedit(t_env **env, char *name, char *val);

void
env_lstdelone(t_env **env, t_env *target);

void
env_lstadd_back(t_env **env, t_env *line);

//env_secure.c
char
*get_pwd(void);

void
env_lstclear(t_env **env);

void
env_secure(t_env **newenv);

//cd.c
void
ft_cd(t_shell *shel, int index);

//extender.c
void
extender(t_shell *shel);

//signals.c
void
sig_handler_classic(void);

void
sig_handler_heredoc(void);

//builtins
void
ft_exit(t_shell *shel, int index);

void
ft_env(t_shell *shel, int index);

void
ft_pwd(t_shell *shel, int index);

void
ft_unset(t_shell *shel, int index);

void
ft_export(t_shell *shel, int index);

void
ft_echo(t_shell *shel, int index);

//utils_stupids.c
void
free_spl(void **s);

int
env_len(t_env *env);

int
array_len(char **array);

//to_sort
bool
is_line_valid(t_shell *shel, char *src);

void
prompt_initializer(t_shell *shel, char **prompt);

void
parse(t_shell *shel, char *src, char **bin);

void
exec(t_shell *shel);

void
env_join(char ***env_ar, t_env *env);

void
arg_cutter(char *arg, char ***cmd_dec);

void
replace(t_shell *shel, char *token, char **token_fill);

int
lexer_handler(t_shell *shel);

int
handle_retcode(t_shell *shel, int *i);

int
len_calc(t_shell *shel, char *token);

void
handle_status(t_quotes *status, char c);

void
update_token(t_shell *shel, t_token **cmd);

void
redir_in(t_cmd *cmd_final, t_token *cur);

void
redir_out_app(t_cmd *cmd_final, t_token *cur);

void
redir_out_err(t_cmd *cmd_final, t_token *cur);

void
free_cmd_dec(t_cmd **cmd_dec);

void
print(t_token *cmd, char *c);

void
reset_state(void);

void
handle_input(t_shell *shel);

int
fill_file(char **delim, int fd, t_shell *shel);

void
redir_here_doc(t_cmd *cmd_final, t_token **cur, t_shell *shel);

void
free_free(t_shell *shel);

void
buid_t_cmd(t_shell *shel, t_cmd **cmd_dec);

int
apply_builtins(t_shell *shel, int index);

int
apply_builtins_forked(t_shell *shel, int index);

void
full_free(t_shell *shel, bool need_exit, int index);

void
close_all_fds(void);

void
close_all(t_cmd curr, int pipefd[2], int in, int out);

t_token
*tkn_lst(t_token *tkn);

void
tkn_delone(t_token *del);

int
cmd_len_calc(t_token *cmd);

void
reset_sig_child(void);

void
hist_adder(t_cmd *cmd_dec, int count, char *src);

void
exec_solo(t_shell *shel);

void
exec_plusplus(t_shell *shel, int count);

void
handle_dup(int arr[2], bool std_dup);

void
handle_pipe(t_shell *shel, int *in, int *out);

void
close_in_out_solo(t_shell *shel);

void
display_errs(t_shell *shel, int index, int status);

void
waiting_solo(t_shell *shel);

void
waiting_plusplus(t_shell *shel, int j, int pidfd[2]);

bool
valid_xprt_name(char *test);

void
ret_code_errs_handle(t_shell *shel);

bool
fail_open(t_cmd *cmd_dec);

void
setup_child(void);

t_env	
**xprt_edit(t_env **env, char *name, char *val);

#endif
