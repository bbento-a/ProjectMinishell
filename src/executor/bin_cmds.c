/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbento-a <bbento-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:04:34 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/15 02:39:06 by bbento-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Prototype for duping process

static void	dup_fds(t_command *cmd)
{
	t_files	*tmp;
	t_files	*fd_in;
	t_files	*fd_out;
	int		fd;

	fd_in = NULL;
	fd_out = NULL;
	tmp = cmd->files;
	while (tmp)
	{
		if (tmp->type == E_HERDOC || tmp->type == E_REDIN)
			fd_in = tmp;
		tmp = tmp->next;
	}
	tmp = cmd->files;
	while (tmp)
	{
		if (tmp->type == E_APPEND || tmp->type == E_REDOUT)
		{
			fd_out = tmp;
		}
		tmp = tmp->next;
	}
	if (fd_in)
	{
		if (fd_in->type == E_HERDOC)
			dup2(fd_in->fd, STDIN_FILENO);
		else
		{
			fd = open(fd_in->file_name, O_RDONLY);
			dup2(fd, STDIN_FILENO);
		}
	}
	if (fd_out)
	{
		if (fd_out->type == E_REDOUT)
			fd = open(fd_out->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (fd_out->type == E_APPEND)
			fd = open(fd_out->file_name, O_CREAT | O_RDWR | O_APPEND, 0644);
		dup2(fd, STDOUT_FILENO);
	}
}


static int	magic_box(char *path, t_command *cmd, t_env *env)
{
	char	**env_array;
	char	*ptr;
	int		pid;
/* 	char *shlvl; */

/* 	shlvl = get_shlvl();
	update_env(&data()->env, shlvl);
	free(shlvl); */

	int ret;
	ret = ERROR; // Initialize ret with a default value
	env_array = NULL;
	if (!path || !cmd->args)
		return (display_err("minishell: ", NULL, \
			"Invalid arguments provided to magic_box", 1));
	child_signals();
	pid = fork();
	if (pid == 0)
	{
		ptr = env_to_str(env);
		if (!ptr)
			exit(ERROR);
		env_array = ft_split(ptr, '\n');
		free(ptr);
		if (env_array)
		{
			if (ft_strchr(path, '/') != NULL)
			{
				dup_fds(cmd);
				if (execve(path, cmd->args, env_array) != 0)
				{
					ret = error_message(cmd->args[0]);
					clear_fork(path, env_array);
				} // If execve fails, we will return the error from error_message
			}
			else
			{
				ret = error_message(path);
				clear_fork(path, env_array);
			}
		}
		exit(ret); // Now, ret will always have a value when passed to exit()
	}
	waitpid(pid, &ret, 0);
	free(path);
	if (env_array)
		free_array(env_array);
	if (WIFSIGNALED(ret)) /// if the process gets terminated by a signal, it returns the value of that signal
	{
		write(1, "\n", 1);
		return (WIFEXITED(ret));
	}
	if (WIFEXITED(ret))
		return (WEXITSTATUS(ret));
	else
		return (ERROR);
}


int	exec_bin(t_command *cmd, t_env *env)
{
	int		i;
	char	**bin;
	char	*path;
	int		ret;
	t_env	*tmp;

	tmp = env;
	ret = 0;
	if (!cmd->args || !cmd->args[0])
		return (data()->exit_code);
	if (cmd->args[0][0] == '.' || cmd->args[0][0] == '/')
		return (magic_box(ft_strdup(cmd->args[0]), cmd, env));
	while (tmp && tmp->value && ft_strncmp(tmp->value, "PATH=", 5) != 0)
		tmp = tmp->next;
	if (!tmp || !tmp->value)
		return (magic_box(ft_strdup(cmd->args[0]), cmd, env));
	bin = ft_split(tmp->value + 5, ':');
	if (!bin)
		return (display_err(NULL, NULL, "Failed to create bin", 1));
	i = 0;
	path = check_dir(bin[i], cmd->args[0]);
	while (!path && bin[++i])
		path = check_dir(bin[i], cmd->args[0]);
	free_array(bin);
	if (path)
		ret = magic_box(path, cmd, env);
	else
		ret = magic_box(ft_strdup(cmd->args[0]), cmd, env);
	return (ret);
}


// valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=all --suppressions=readline.supp --track-fds=yes ./minishell
