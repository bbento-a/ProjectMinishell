/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mtmpfb@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:37:59 by mde-maga          #+#    #+#             */
/*   Updated: 2025/01/24 15:45:23 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int		is_builtin(char *command)
{
	if (ft_strcmp(command, "echo") == 0)
		return (1);
	if (ft_strcmp(command, "cd") == 0)
		return (1);
	if (ft_strcmp(command, "pwd") == 0)
		return (1);
	if (ft_strcmp(command, "env") == 0)
		return (1);
	if (ft_strcmp(command, "export") == 0)
		return (1);
	if (ft_strcmp(command, "unset") == 0)
		return (1);
	return (0);
}

int exec_builtin(char **args, t_mini *mini)
{
    int result = 0;

    if (ft_strcmp(args[0], "echo") == 0)
        result = ms_echo(args);
    else if (ft_strcmp(args[0], "cd") == 0)
        result = ms_cd(args, mini->env);
   else if (ft_strcmp(args[0], "pwd") == 0)
    	result = ms_pwd();
    else if (ft_strcmp(args[0], "env") == 0)
    {
        ms_env(mini->env); 
        result = SUCCESS; 
    }
    else if (ft_strcmp(args[0], "export") == 0)
    {
        ms_export(mini, args); 
        result = mini->ret; 
    }
    else if (ft_strcmp(args[0], "unset") == 0)
    {
        ms_unset(mini, args); 
        result = mini->ret; 
    }

    return (result);
}

