/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mtmpfb@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:11:18 by mde-maga          #+#    #+#             */
/*   Updated: 2025/01/24 15:39:30 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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