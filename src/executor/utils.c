/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbento-a <bbento-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:49:24 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/15 08:02:57 by bbento-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*env_to_str(t_env *env)
{
	char	*str;
	size_t	len;
	t_env	*tmp;

	len = 0;
	tmp = env;
	while (tmp)
	{
		if (tmp->value)
			len += ft_strlen(tmp->value) + 1;
		tmp = tmp->next;
	}
	str = my_malloc(len + 1);
	if (!str)
		return (NULL);
	str[0] = '\0';
	{
		if (env->value)
			ft_strlcat(str, env->value, len + 1);
		ft_strlcat(str, "\n", len + 1);
		env = env->next;
	}
	return (str);
}

void	free_tab(char **array)
{
	if (!array)
		return ;
	free(array);
}

int	handle_error(char *path, DIR *folder, int fd)
{
	if (ft_strchr(path, '/') == NULL)
		ft_putendl_fd(": command not found", STDERR);
	else if (fd == -1 && folder == NULL)
		ft_putendl_fd(": No such file or directory", STDERR);
	else if (fd == -1 && folder != NULL)
		ft_putendl_fd(": Is a directory", STDERR);
	else if (fd != -1 && folder == NULL)
		ft_putendl_fd(": Permission denied", STDERR);
	if (ft_strchr(path, '/') == NULL || (fd == -1 && folder == NULL))
		return (UNKNOWN_COMMAND);
	return (IS_DIRECTORY);
}

int	look_for_fds(t_command *cmd)
{
	t_files	*file;
	t_files	*tmp;
	int		fd;

	file = NULL;
	tmp = cmd->files;
	while (tmp)
	{
		if (tmp->type == E_REDOUT || tmp->type == E_APPEND)
			file = tmp;
		tmp = tmp->next;
	}
	if (!file)
		return (STDOUT);
	else
	{
		if (file->type == E_APPEND)
			fd = open(file->file_name, O_RDWR | O_APPEND);
		else
			fd = open(file->file_name, O_RDWR);
		return (fd);
	}
}
