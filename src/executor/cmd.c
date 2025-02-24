/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbento-a <bbento-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:37:59 by mde-maga          #+#    #+#             */
/*   Updated: 2025/02/21 17:47:29 by bbento-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int		is_builtin(char *command)
{
	if (ft_strncmp(command, "echo", 4) == 0)
		return (1);
	if (ft_strncmp(command, "cd", 2) == 0)
		return (1);
	if (ft_strncmp(command, "pwd", 3) == 0)
		return (1);
	if (ft_strncmp(command, "env", 3) == 0)
		return (1);
	if (ft_strncmp(command, "export", 6) == 0)
		return (1);
	if (ft_strncmp(command, "unset", 5) == 0)
		return (1);
	if (ft_strncmp(command, "exit", 4) == 0)
		return (1);
	return (0);
}
/// Changed return values

int exec_builtin(char **args)
{
	if (ft_strncmp(args[0], "echo", 4) == 0)
		return (ms_echo(args));
	else if (ft_strncmp(args[0], "cd", 2) == 0)
		return (ms_cd(args, data()->env));
	else if (ft_strncmp(args[0], "pwd", 3) == 0)
		return (ms_pwd());
    else if (ft_strncmp(args[0], "env", 3) == 0)
        return (ms_env(data()->env));
    else if (ft_strncmp(args[0], "export", 6) == 0)
        return (ms_export(args));
    else if (ft_strncmp(args[0], "unset", 5) == 0)
        return (ms_unset(args)); 
	else if (ft_strncmp(args[0], "exit", 4) == 0)
		return(builtin_exit(args));
	return (0);
}

