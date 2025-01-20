
#ifndef MINISHELL_H
# define MINISHELL_H

//
//  LIBRARIES, HEADERS AND MACROS
//

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <signal.h>
# include <fcntl.h>
# include <string.h>
# include <syscall.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <termios.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

# define DEFAULT_SHLVL	"1"
# define PIPE_READ		0
# define PIPE_WRITE		1

//
//  STUCTS
//

typedef struct s_files		t_files;
typedef struct s_command	t_command;

typedef enum e_type
{
	E_REDIN,
	E_REDOUT,
	E_APPEND,
	E_HERDOC,
	E_PIPE,
	E_OTHER,
}	t_type;

typedef struct s_files
{
	char		*file_name;
	int			fd;
	bool		hq_limiter;
	t_type		type;

	t_files		*previous;
	t_files		*next;
}	t_files;

typedef struct s_command
{
	char			*path;
	char			**args;

	int				fd_in;
	int				fd_out;
	t_files			*in_file;
	t_files			*out_file;

	int				pipe_fd[2];
	bool			pipe_is_active;

	int				is_builtin; //stores index in builtin array
	int				exit_status;
	pid_t			pid;

	t_command		*next;
	t_command		*previous;
}	t_command;

typedef struct s_line
{
	char			*content;
	char			type_q;
	bool			white_space;
	bool			arg;
	t_type			type_n;

	struct s_line	*prev;
	struct s_line	*next;
}	t_line;

typedef struct s_builtin
{
	char	*name;
	int		(*func)(t_command *command);
}	t_builtin;

typedef struct s_minishell
{
	char		**env;
	char		hld_flag; // hold flag for quotes
	int			exit_code;
	int			last_exit_status;
	bool		prompt_flag; // signals flag
	bool		error_parse;

	t_builtin	*builtin_list;
	t_line		*prompt;
	t_command	*cmds;

}	t_minishell;

//
//	FUNCTIONS
//

//
//	PARSING
//

// parser.c
// int			parse_line(char *line);
int			parsing_input(char *line);

// lexer.c
int			syntax_checker(char *line, t_line **prompt);

// search_expan.c
int			search_expansion(t_line **input);

// expander.c
char		*expand_token(char *str);
char		*replace_var(char *str, char *value, int var_bgn, int nvar_len);

// post_expansion.c
int			handle_post_expansion(t_line **input, t_line *prompt);

// handle_wspaces.c
int			handle_wspaces(t_line *prompt);

// parse_list.c
void		check_token_syntax(t_line *tokens);
t_command	*parse_list(t_line *tokens);

// handle_cmd_args.c
int			handle_node_args(t_line *bgn, t_line *last);
void		make_cmd_args(char **args, t_line *bgn, t_line *last, int size);

// handle_list_nodes.c
void		add_cmds_last(t_command **cmds, t_command *node);
t_files		*make_cmd_files(t_line *bgn, t_line *last, char flg);

//
//	EXECUTOR
//

int			builtin_exit(t_command *command);

char		*get_env(char *var);


//
//	MISCELLANEOUS
//

// data.c
t_minishell	*data(void);
void		init_data(char **envp);

// exit_functions.c
int			display_err(char *local, char *arg, char *error_msg, int err_code);

// free_functions.c
void		free_files(t_files	*files);
void		free_cmds(t_command **cmds);
void		free_builtin_list(t_builtin *builtin_list);
void		free_list(t_line *prompt);
void		clear_linelst(t_line **lst);
void		clear_memory(t_command **commands);

// ft_functions.c
bool		symbol_cmp(char *sign, char c);
void		define_flg(char c);
int			ft_mtxlen(char **mtx);
void		ft_freemtx(char **mtx);
int			ft_close(int *fd);
void		define_white_space(t_line *node, char *line, int bgn);
t_type		define_type(t_line *node);
int			is_builtin(char *command_name);

// lst_functions.c
t_line		*find_lastnode(t_line *lst);

// signals.c
int			check_input(char *line);

// new_signals.c
void		environment_signals(void);
void		child_signals(void);
void		heredoc_signals(void);
void		disable_signals(void);

// ft_debug.c
void		ft_printmtx(char **mtx);
void		ft_printlist(t_line *lst);
void		test(t_command *cmds);
void		print_filenodes(t_files *files);
void		ft_printfiles(t_files *files);

#endif