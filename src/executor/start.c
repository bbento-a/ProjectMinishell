/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mtmpfb@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:42:40 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/15 09:17:08 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exec_cmd(t_command *command)
{
	int	ret_val;

	if (command->next)
		ret_val = handle_pipes(command, data()->env);
	else
		ret_val = exec_bin(command, data()->env);
	return (ret_val);
}

void	handle_parent_process(pid_t pid, int *prev_fd, int pipefd[2],
		t_command **cmds)
{
	waitpid(pid, NULL, 0);
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
