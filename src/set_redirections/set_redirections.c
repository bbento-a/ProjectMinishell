/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbento-a <bbento-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 02:49:10 by bbento-a          #+#    #+#             */
/*   Updated: 2025/03/15 07:29:04 by bbento-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	redirection_validation(t_files *file)
{
	DIR	*access_file;
	int	fd;

	if (!file)
		return (-1);
	access_file = opendir(file->file_name);
	if (file->type == E_REDIN)
		fd = open(file->file_name, O_RDONLY);
	else if (file->type == E_REDOUT)
		fd = open(file->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (file->type == E_APPEND)
		fd = open(file->file_name, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd == -1)
	{
		if(access(file->file_name, F_OK) < 0)
			return (display_err("minishell: ", file->file_name,
				": No such file or directory", 1));
		else if (access(file->file_name, X_OK) < 0)
			return (display_err("minishell: ", file->file_name,
				": Permission denied", 1));
	}
	close(fd);
	if (access_file)
		closedir(access_file);
	return (0);
}

int	heredoc_validation(t_files *file)
{
	int	fd;

	fd = heredocument(file->file_name, file->hq_limiter);
	if (data()->error_parse)
	{
		close(fd);
		return (1);
	}
	file->fd = fd;
	return (0);
}

int	check_heredocs(t_files *files)
{
	t_files	*tmp;

	tmp = files;
	while (tmp)
	{
		if (tmp->type == E_HERDOC && heredoc_validation(tmp))
			return (1); // turns command invalid, it doesn't even need to build it's path
		tmp = tmp->next;
	}
	return (0);
}

int	check_command_redirections(t_files *files)
{
	t_files	*tmp;

	tmp = files;
	while (tmp)
	{
		if (tmp->type != E_HERDOC && redirection_validation(tmp))
			return (1); // turns command invalid, it doesn't even need to build it's path
		tmp = tmp->next;
	}
	return (0);
}

int	check_redirections(t_command *cmds)
{
	t_command	*cmd;

	cmd = cmds;
	while (cmd)
	{
		if (check_heredocs(cmd->files))
			return (1);
		cmd = cmd->next;
	}
	cmd = cmds;
	while (cmd)
	{
		if (check_command_redirections(cmd->files) == 1)
		{
			free_array(cmds->args);
			(cmds->args) = NULL;
		}
		cmd = cmd->next;
	}
	return (0);
}
