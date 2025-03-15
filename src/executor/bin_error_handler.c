/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_error_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mtmpfb@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 07:15:27 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/15 07:32:51 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	handle_error_message(char *path, DIR *folder, int fd)
{
	int	ret;

	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(path, STDERR);
	ret = handle_error(path, folder, fd);
	if (folder)
		closedir(folder);
	if (fd != -1)
		close(fd);
	return (ret);
}

int	error_message(char *path)
{
	DIR	*folder;
	int	fd;

	if (!path)
		return (display_err("minishell: ", NULL, "NULL path provided", 1));
	fd = open(path, O_WRONLY);
	folder = opendir(path);
	return (handle_error_message(path, folder, fd));
}

int	wait_for_child_process(int pid, char *path, char **env_array)
{
	int	ret;

	waitpid(pid, &ret, 0);
	free(path);
	if (env_array)
		free_array(env_array);
	if (WIFSIGNALED(ret))
	{
		write(1, "\n", 1);
		return (WIFEXITED(ret));
	}
	if (WIFEXITED(ret))
		return (WEXITSTATUS(ret));
	return (ERROR);
}
