/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbento-a <bbento-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 02:33:48 by bbento-a          #+#    #+#             */
/*   Updated: 2025/03/15 02:39:50 by bbento-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	error_message(char *path)
{
	DIR	*folder;
	int	fd;
	int	ret;

	if (!path)
		return (display_err("minishell: ", NULL, "NULL path provided", 1));
	fd = open(path, O_WRONLY);
	folder = opendir(path);
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(path, STDERR);
	ret = handle_error(path, folder, fd);
	if (folder)
		closedir(folder);
	if (fd != -1)
		close(fd);
	return (ret);
}

char	*path_join(const char *s1, const char *s2)
{
	char	*tmp;
	char	*path;

	if (!s1 || !s2)
		return (NULL);
	tmp = ft_strjoin(s1, "/");
	if (!tmp)
		return (NULL);
	path = ft_strjoin(tmp, s2);
	free(tmp);
	return (path);
}

char	*check_dir(char *bin, char *command)
{
	DIR				*folder;
	struct dirent	*item;
	char			*path;

	if (!bin || !command)
		return (NULL);
	folder = opendir(bin);
	if (!folder)
		return (NULL);
	path = NULL;
	while ((item = readdir(folder)))
	{
		if (ft_strncmp(item->d_name, command, ft_strlen(item->d_name)) == 0)
		{
			path = path_join(bin, command);
			break ;
		}
	}
	closedir(folder);
	return (path);
}