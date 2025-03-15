/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbento-a <bbento-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 06:02:24 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/15 08:04:17 by bbento-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	display_err(char *local, char *arg, char *error_msg, int err_code)
{
	if (local)
		ft_putstr_fd(local, 2);
	if (arg)
		ft_putstr_fd(arg, 2);
	ft_putendl_fd(error_msg, 2);
	data()->exit_code = err_code;
	if (err_code < 0)
		data()->exit_code = 1;
	return (err_code);
}

void	clear_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		free(env->value);
		env->envp = NULL;
		tmp = env;
		env = env->next;
		free(tmp);
	}
	env = NULL;
}

void	clear_cmd_files(t_files **files)
{
	t_files	*tmp;

	if (!files || !*files)
		return ;
	while (*files)
	{
		if ((*files)->type == E_HERDOC && (*files)->fd > 2)
			close((*files)->fd);
		free((*files)->file_name);
		(*files)->file_name = NULL;
		tmp = *files;
		*files = (*files)->next;
		free(tmp);
	}
	files = NULL;
}

void	clear_memory(t_command *cmds)
{
	t_command	*temp;

	while (cmds)
	{
		if (cmds->args)
		{
			free_array(cmds->args);
		}
		clear_cmd_files(&cmds->files);
		temp = cmds;
		cmds = cmds->next;
		free(temp);
	}
	cmds = NULL;
}

void	clear_fork(char *path, char **env_array)
{
	free(path);
	free_array(env_array);
	clear_memory(data()->cmds);
	clear_env(data()->env);
}
