/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magic_bin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mtmpfb@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 06:15:01 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/19 19:12:24 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	**allocate_env_array(t_env *env)
{
	char	**env_array;
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	env_array = malloc(sizeof(char *) * (i + 1));
	if (!env_array)
		return (NULL);
	return (env_array);
}

static int	copy_env_variables(t_env *env, char **env_array)
{
	t_env	*tmp;
	int		i;

	tmp = env;
	i = 0;
	while (tmp)
	{
		env_array[i] = ft_strdup(tmp->value);
		if (!env_array[i])
			return (0);
		tmp = tmp->next;
		i++;
	}
	env_array[i] = NULL;
	return (1);
}

static int	handle_magic_box_errors(char *path, t_command *cmd)
{
	if (!path || !cmd->args)
		return (display_err("minishell: ", NULL,
				"Invalid arguments provided to magic_box", 1));
	return (0);
}

int	fork_and_exec(char *path, t_command *cmd, char **env_array)
{
	int	pid;
	int	ret;

	pid = fork();
	ret = 1;
	if (pid == 0)
	{
		dup_fds(cmd);
		if (execve(path, cmd->args, env_array) != 0)
			ret = error_message(cmd->args[0]);
		clear_fork(path, env_array);
		exit(ret);
	}
	return (pid);
}

int	magic_box(char *path, t_command *cmd, t_env *env)
{
	char	**env_array;
	int		ret;
	int		pid;

	env_array = NULL;
	ret = ERROR;
	if (env)
	{
		env_array = allocate_env_array(env);
		if (!env_array || !copy_env_variables(env, env_array))
			return (display_err("minishell: ", NULL, "Memory allocation failed",
					1));
	}
	if (handle_magic_box_errors(path, cmd))
		return (ret);
	child_signals();
	pid = fork_and_exec(path, cmd, env_array);
	if (pid == 0)
		return (ret);
	return (wait_for_child_process(pid, path, env_array));
}
