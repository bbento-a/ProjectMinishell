/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mtmpfb@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 02:34:52 by bbento-a          #+#    #+#             */
/*   Updated: 2025/03/15 09:17:25 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	create_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
		return (display_err(NULL, NULL, "Failed to open pipe", 1));
	return (0);
}

pid_t	create_process(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		display_err(NULL, NULL, "Failed to fork process", 1);
	return (pid);
}

void	handle_child_process(t_command *cmds, int prev_fd, int pipefd[2],
		t_env *env)
{
	int	status;

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

static int	execute_process(pid_t pid, t_command *cmds, int *prev_fd,
		int pipefd[2])
{
	if (pid == -1)
		return (1);
	if (pid == 0)
		handle_child_process(cmds, *prev_fd, pipefd, data()->env);
	else
		handle_parent_process(pid, prev_fd, pipefd, &cmds);
	return (0);
}

int	handle_pipes(t_command *cmds, t_env *env)
{
	int		pipefd[2];
	int		prev_fd;
	int		i;
	int		status;
	pid_t	pid;

	prev_fd = -1;
	i = 0;
	status = 1;
	if (env)
		printf("Env pointer is valid\n");
	while (cmds)
	{
		if (cmds->next && create_pipe(pipefd))
			return (1);
		pid = create_process();
		if (execute_process(pid, cmds, &prev_fd, pipefd))
			return (1);
		i++;
	}
	while (--i > 0)
		wait(NULL);
	return (status);
}
