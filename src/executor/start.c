/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbento-a <bbento-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:42:40 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/17 15:49:03 by bbento-a         ###   ########.fr       */
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
