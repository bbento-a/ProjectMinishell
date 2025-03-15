/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbento-a <bbento-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:30:06 by bbento-a          #+#    #+#             */
/*   Updated: 2025/03/15 02:45:56 by bbento-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// After checking redirections, we start executing here

int	executor(t_command *command)
{
	disable_signals();
	if (!command->next && command->args && is_builtin(command->args[0]))
	{
		return (exec_builtin(command)); // Execute built-in command
	}
	else
		return (exec_cmd(command));
}

int	check_and_execute(t_command *commands)
{
	if (!commands)
		return (1);
	if (check_redirections(commands)) // if terminated by SIGINT
	{
		clear_memory(commands);
		clear_env(data()->env);
		return (1);
	}
	data()->exit_code = executor(commands);
	return (0);
}
