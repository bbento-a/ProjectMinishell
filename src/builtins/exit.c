/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbento-a <bbento-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:18:14 by mde-maga          #+#    #+#             */
/*   Updated: 2025/02/21 16:25:56 by bbento-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool is_digit(const char *s)
{
    while (*s)
    {
        if (!ft_isdigit(*s))
            return false;
        s++;
    }
    return true;
}

int ms_exit(t_mini *mini, char **cmd)
{
    mini->exit = 1; // Indicate that the shell should exit
    ft_putstr_fd("exit\n", STDERR);

    if (cmd[1] && cmd[2]) // More than one argument provided
    {
        mini->ret = 1; // Set return code for "too many arguments"
        ft_putendl_fd("minishell: exit: too many arguments", STDERR);
        return; // Do not exit immediately; allow the shell to continue
    }
    if (cmd[1] && !is_digit(cmd[1])) // Invalid numeric argument
    {
        mini->ret = 255; // Set exit code for error
        ft_putstr_fd("minishell: exit: ", STDERR);
        ft_putstr_fd(cmd[1], STDERR);
        ft_putendl_fd(": numeric argument required", STDERR);
        exit(255); // Exit with error code
    }
    // Exit with the given code, or 0 if no argument is provided
    mini->ret = cmd[1] ? ft_atoi(cmd[1]) : 0;
    exit(mini->ret);
}
