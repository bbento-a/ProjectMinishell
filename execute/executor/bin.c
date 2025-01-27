/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mtmpfb@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:04:34 by mde-maga          #+#    #+#             */
/*   Updated: 2025/01/27 12:08:13 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"


int error_message(char *path)
{
    DIR *folder = NULL;
    int fd = -1;
    int ret;

    if (!path) {
        ft_putendl_fd("minishell: NULL path provided", STDERR);
        return (ERROR);
    }

    fd = open(path, O_WRONLY);
    folder = opendir(path);

    ft_putstr_fd("minishell: ", STDERR);
    ft_putstr_fd(path, STDERR);

    if (ft_strchr(path, '/') == NULL)
        ft_putendl_fd(": command not found", STDERR);
    else if (fd == -1 && folder == NULL)
        ft_putendl_fd(": No such file or directory", STDERR);
    else if (fd == -1 && folder != NULL)
        ft_putendl_fd(": is a directory", STDERR);
    else if (fd != -1 && folder == NULL)
        ft_putendl_fd(": Permission denied", STDERR);

    if (ft_strchr(path, '/') == NULL || (fd == -1 && folder == NULL))
        ret = UNKNOWN_COMMAND;
    else
        ret = IS_DIRECTORY;

    if (folder)
        closedir(folder);
    if (fd != -1)
        close(fd);

    return (ret);
}


