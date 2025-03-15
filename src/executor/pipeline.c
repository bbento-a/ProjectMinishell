/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbento-a <bbento-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 02:34:52 by bbento-a          #+#    #+#             */
/*   Updated: 2025/03/15 08:19:22 by bbento-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
