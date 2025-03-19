/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mtmpfb@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 02:13:07 by bbento-a          #+#    #+#             */
/*   Updated: 2025/03/19 19:13:06 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

# include "builtins.h"
# include "minishell.h"
# include <dirent.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <syscall.h>

typedef struct s_env
{
	char			*value;
	struct s_env	*next;
	char			**envp;
}					t_env;

int					check_and_execute(t_command *commands);
int					check_redirections(t_command *cmds);
int					heredocument(char *limiter, bool quotes);

int					exec_bin(t_command *cmd, t_env *env);
int					handle_pipes(t_command *cmds);

int					ft_strcmp(const char *s1, const char *s2);
int					is_builtin(char *command);
int					exec_builtin(t_command *cmd);

int					exec_cmd(t_command *commnad);

int					error_message(char *path);
char				*path_join(const char *s1, const char *s2);
char				*check_dir(char *bin, char *command);

char				*env_to_str(t_env *env);
void				free_tab(char **array);
int					handle_error(char *path, DIR *folder, int fd);

int					look_for_fds(t_command *cmd);

void				dup_fds(t_command *cmd);
void				dup_out_fd(t_files *fd_out);
void				dup_in_fd(t_files *fd_in);
int					fork_and_exec(char *path, t_command *cmd, char **env_array);
int					error_message(char *path);
int					handle_error_message(char *path, DIR *folder, int fd);
int					wait_for_child_process(int pid, char *path,
						char **env_array);
int					magic_box(char *path, t_command *cmd, t_env *env);
void				handle_parent_process(int *prev_fd, int pipefd[2],
						t_command **cmds);

size_t				ft_strlen_equal(const char *str);
int					wait_cmds(pid_t pid, int status);

#endif