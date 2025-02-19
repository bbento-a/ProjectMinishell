
#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef struct s_command	t_command;
typedef struct s_files		t_files;

typedef enum e_type
{
	E_REDIN,
	E_REDOUT,
	E_APPEND,
	E_HERDOC,
	E_PIPE,
	E_OTHER,
}	t_type;

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

typedef struct s_command
{
	char			**args;
	char			*path;

	int				fd_in;
	int				fd_out;
	t_files			*files;

	int				exit_status;
	pid_t			pid;

	t_command		*next;
	t_command		*previous;
}	t_command;

typedef struct s_files
{
	char		*file_name;
	int			fd;
	bool		hq_limiter;
	t_type		type;

	t_files		*previous;
	t_files		*next;
}	t_files;

// parser.c
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
int			parse_list(t_line *tokens, t_command **cmds);

// handle_cmd_args.c
int			handle_node_args(t_line *bgn, t_line *last);
void		make_cmd_args(char **args, t_line *bgn, t_line *last, int size);

// handle_list_nodes.c
void		add_cmds_last(t_command **cmds, t_command *node);
t_files		*make_cmd_files(t_line *bgn, t_line *last);

#endif