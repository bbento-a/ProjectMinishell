
#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

typedef struct s_builtin
{
	char	*name;
	int		(*func)(t_command *command);
}	t_builtin;

int		builtin_exit(char **args);
int		ms_cd(char **args, t_env *env);
int		ms_echo(char **args);
int		ms_env(t_env *env);
int		ms_export(char **cmd);
int		ms_pwd(void);
int		ms_unset(char **cmd);
char	*get_env_path(t_env *env, const char *var, size_t len);
int		update_oldpwd(t_env *env);
void	ft_memdel(void **ap);
void	env_add(char *var, t_env *env);
int 	is_in_env(t_env *env, const char *var);

// int		ms_exit(t_mini *mini, char **cmd);

#endif