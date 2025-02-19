/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbento-a <bbento-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:11:18 by mde-maga          #+#    #+#             */
/*   Updated: 2025/02/19 16:42:50 by bbento-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
int ms_pwd(void)
{
    char cwd[PATH_MAX];

    if (getcwd(cwd, PATH_MAX))
    {
        ft_putendl_fd(cwd, STDOUT); // Print current working directory
        return (SUCCESS); // Return success code
    }
    else
    {
        ft_putstr_fd("Error: Unable to get current working directory\n", STDERR);
        return (ERROR); // Return error code
    }
}