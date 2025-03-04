/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbento-a <bbento-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:30:06 by bbento-a          #+#    #+#             */
/*   Updated: 2025/03/04 15:32:10 by bbento-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// After checking redirections, we start executing here

int	executor(t_command *command)
{
	disable_signals();
	if (!command->next && is_builtin(command->args[0]))
	{
		return (exec_builtin(command->args)); // Execute built-in command
	}
	else
	{
		return (exec_cmd(command));
			// Execute non-built-in commands (external binaries)
	}
}

int	check_and_execute(t_command *commands)
{
	if (!commands)
		return (1);
	if (check_redirections(commands)) // if terminated by SIGINT
	{
		// clean_up close_fds
		return (1);
	}
	data()->exit_code = executor(commands);
	return (0);
}
