/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mtmpfb@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:18:11 by mde-maga          #+#    #+#             */
/*   Updated: 2025/02/11 12:21:22 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#ifndef PATH_MAX
# define PATH_MAX 4096

# include "../utils/libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <limits.h>
# include <errno.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <stdbool.h>
# include <dirent.h>
# include <fcntl.h>

# define EMPTY 0
# define CMD 1
# define ARG 2
# define TRUNC 3
# define APPEND 4
# define INPUT 5
# define PIPE 6
# define END 7

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define SKIP 1
# define NOSKIP 0

# define BUFF_SIZE 4096
# define EXPANSION -36
# define ERROR 1
# define SUCCESS 0
# define IS_DIRECTORY 126
# define UNKNOWN_COMMAND 127


typedef struct	s_token
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

typedef struct	s_env
{
	char			*value;
	struct s_env	*next;
	char **envp;
}				t_env;

typedef struct	s_sig
{
	int				sigint;
	int				sigquit;
	int				exit_status;
	pid_t			pid;
}				t_sig;

extern t_sig g_sig;

typedef struct	s_mini
{
	t_token			*start;
	t_env			*env;
	t_env			*other_env;
	int				in;
	int				out;
	int				fdin;
	int				fdout;
	int				pipein;
	int				pipeout;
	int				pid;
	int				charge;
	int				parent;
	int				last;
	int				ret;
	int				exit;
	int				no_exec;
}				t_mini;



int ms_cd(char **args, t_env *env);
int	ms_echo(char **args);
void ms_env(t_env *env);
void ms_exit(t_mini *mini, char **cmd);
void	ms_export(t_mini *mini, char **cmd);
int	ms_pwd(void);
void	ms_unset(t_mini *mini, char **cmd);
char *get_env_path(t_env *env, const char *var, size_t len);
int update_oldpwd(t_env *env);
void ft_memdel(void **ap);
void env_add(char *var, t_env *env);
int is_in_env(t_env *env, const char *var);

int			error_message(char *path);
int			magic_box(char *path, char **args, t_env *env, t_mini *mini);
char		*path_join(const char *s1, const char *s2);
char		*check_dir(char *bin, char *command);
int			exec_bin(char **args, t_env *env, t_mini *mini);

int		is_builtin(char *command);
int		exec_builtin(char **args, t_mini *mini);

char	**cmd_tab(t_token *start);
void	exec_cmd(t_mini *mini, t_token *token);

char 	*env_to_str(t_env *env);
void free_tab(char **array);
void free_token(t_token *token);
int handle_error(char *path, DIR *folder, int fd);

void	mini_exit(t_mini *mini, char **cmd);
void	ft_close(int fd);
int	has_pipe(t_token *token);
char	*expansions(char *cmd, t_env *env, int ret);
char	*expand_variable(char *str, t_env *env);

void handle_signal(int sig);
int main(int argc, char **argv, char **envp);
void parse_envp(char **envp, t_mini *mini);
t_token *token_parser(char *line);


#endif
#endif
