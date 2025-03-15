
#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include "executor.h"

typedef struct	s_env t_env;

int		builtin_exit(char **args);
int		ms_cd(char **args, t_env *env);
int		ms_echo(t_command *cmd, char **args);
int		ms_env(t_command *cmd, t_env *env);
int		ms_pwd(t_command *cmd);
int		ms_export(t_command *cmd, char **args);
int		ms_unset(char **cmd);
int		update_env(t_env **env, const char *var);
char	*get_env_path(t_env *env, const char *var, size_t len);
int		update_oldpwd(t_env **env);
int		update_pwd(t_env **env);
void	ft_memdel(void **ap);
// void	env_add(char *var, t_env *env);
int 	is_in_env(t_env *env, const char *var);

#endif