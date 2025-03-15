/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbento-a <bbento-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 02:12:29 by bbento-a          #+#    #+#             */
/*   Updated: 2025/03/15 08:24:21 by bbento-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "executor.h"
# include "minishell.h"

typedef struct s_env	t_env;

int			builtin_exit(char **args);
int			ms_cd(char **args, t_env *env);
int			ms_echo(t_command *cmd, char **args);
int			ms_env(t_command *cmd, t_env *env);
int			ms_pwd(t_command *cmd);
int			ms_export(t_command *cmd, char **args);
int			ms_unset(char **cmd);

int			is_in_env(t_env *env, const char *var);
int			is_valid_env(const char *s);
void		print_env(t_command *cmd, t_env *env);
int			update_env(t_env **env, const char *var);
char		*get_env_path(t_env *env, const char *var, size_t len);
int			update_oldpwd(t_env **env);
int			update_pwd(t_env **env);
void		ft_memdel(void **ap);
int			is_in_env(t_env *env, const char *var);

#endif