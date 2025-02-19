
#ifndef EXECUTOR_H
# define EXECUTOR_H

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

# include "minishell.h"
# include "minishell2.h"
# include "builtins.h"

int		check_and_execute(t_command *commands);
int		check_redirections(t_command *cmds);

int		is_builtin(char *command);
int		exec_builtin(char **args, t_mini *mini);

char	**cmd_tab(t_token *start);
void	exec_cmd(t_mini *mini, t_token *token);

char 	*env_to_str(t_env *env);
void	free_tab(char **array);
void	free_token(t_token *token);
int		handle_error(char *path, DIR *folder, int fd);

void	mini_exit(t_mini *mini, char **cmd);
void	ft_close(int fd);
int		has_pipe(t_token *token);

#endif