/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mtmpfb@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:42:40 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/19 19:11:15 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exec_cmd(t_command *command)
{
	int	ret_val;

	if (command->next)
		ret_val = handle_pipes(command);
	else
		ret_val = exec_bin(command, data()->env);
	return (ret_val);
}

void	handle_parent_process(int *prev_fd, int pipefd[2],
		t_command **cmds)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if ((*cmds)->next)
	{
		close(pipefd[1]);
		*prev_fd = pipefd[0];
	}
	else
		close(pipefd[0]);
	*cmds = (*cmds)->next;
}

int	wait_cmds(pid_t pid, int status)
{
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		status = WIFEXITED(status);
	else if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	return (status);
}
