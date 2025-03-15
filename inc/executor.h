
#ifndef EXECUTOR_H
# define EXECUTOR_H

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define ERROR 1
# define SUCCESS 0
# define IS_DIRECTORY 126
# define UNKNOWN_COMMAND 127


# include <string.h>
# include <syscall.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>

# include "minishell.h"
# include "builtins.h"

typedef struct	s_env
{
	char			*value;
	struct s_env	*next;
	char **envp;
}				t_env;

int		check_and_execute(t_command *commands);
int		check_redirections(t_command *cmds);

int		exec_bin(t_command *cmd, t_env *env);
int		handle_pipes(t_command *cmds, t_env *env);

int		ft_strcmp(const char *s1, const char *s2);
int		is_builtin(char *command);
int		exec_builtin(t_command *cmd);

int		exec_cmd(t_command *commnad);

char 	*env_to_str(t_env *env);
void	free_tab(char **array);
int		handle_error(char *path, DIR *folder, int fd);

int		look_for_fds(t_command *cmd);

#endif