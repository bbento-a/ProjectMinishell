/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mtmpfb@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 04:45:38 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/15 07:28:20 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	dup_in_fd(t_files *fd_in)
{
	int	fd;

	if (fd_in->type == E_HERDOC)
		dup2(fd_in->fd, STDIN_FILENO);
	else
	{
		fd = open(fd_in->file_name, O_RDONLY);
		dup2(fd, STDIN_FILENO);
	}
}

void	dup_out_fd(t_files *fd_out)
{
	int	fd;

	if (fd_out->type == E_REDOUT)
		fd = open(fd_out->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (fd_out->type == E_APPEND)
		fd = open(fd_out->file_name, O_CREAT | O_RDWR | O_APPEND, 0644);
	dup2(fd, STDOUT_FILENO);
}

void	dup_fds(t_command *cmd)
{
	t_files	*tmp;
	t_files	*fd_in;
	t_files	*fd_out;

	fd_in = NULL;
	fd_out = NULL;
	tmp = cmd->files;
	while (tmp)
	{
		if (tmp->type == E_HERDOC || tmp->type == E_REDIN)
			fd_in = tmp;
		else if (tmp->type == E_APPEND || tmp->type == E_REDOUT)
			fd_out = tmp;
		tmp = tmp->next;
	}
	if (fd_in)
		dup_in_fd(fd_in);
	if (fd_out)
		dup_out_fd(fd_out);
}

int	handle_pipes(t_command *cmds, t_env *env)
{
	int		pipefd[2];
	int		prev_fd;
	int		i;
	pid_t	pid;
	int		status;

	prev_fd = -1;
	i = 0;
	status = 1;
	while (cmds)
	{
		if (cmds->next && pipe(pipefd) == -1)
			return (display_err(NULL, NULL, "Failed to open pipe", 1));
		pid = fork();
		if (pid == -1)
			return (display_err(NULL, NULL, "Failed to fork process", 1));
		if (pid == 0)
		{
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (cmds->next)
			{
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[1]);
				close(pipefd[0]);
			}
			if (cmds->args && is_builtin(cmds->args[0]))
				status = exec_builtin(cmds);
			else
				status = exec_bin(cmds, env);
			clear_memory(data()->cmds);
			clear_env(data()->env);
			exit(status);
		}
		else
		{
			if (prev_fd != -1)
				close(prev_fd);
			if (cmds->next)
			{
				close(pipefd[1]);
				prev_fd = pipefd[0];
			}
			else
				close(pipefd[0]);
			cmds = cmds->next;
			i++;
		}
	}
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		status = WIFEXITED(status);
	else if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	while (--i > 0)
		wait(NULL);
	return (status);
}
