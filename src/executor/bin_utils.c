/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 04:45:38 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/24 10:50:20 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	dup_in_fd(t_files *fd_in)
{
	int	fd;

	if (fd_in->type == E_HERDOC)
	{
		fd = fd_in->fd;
		dup2(fd, STDIN_FILENO);
	}
	else
	{
		fd = open(fd_in->file_name, O_RDONLY);
		dup2(fd, STDIN_FILENO);
	}
	close(fd);
}

void	dup_out_fd(t_files *fd_out)
{
	int	fd;

	fd = -1;
	if (fd_out->type == E_REDOUT)
		fd = open(fd_out->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (fd_out->type == E_APPEND)
		fd = open(fd_out->file_name, O_CREAT | O_RDWR | O_APPEND, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	dup_fds(t_command *cmd)
{
	t_files	*tmp;
	t_files	*fd_in;
	t_files	*fd_out;

	fd_in = NULL;
	fd_out = NULL;
	tmp = cmd->files;
	while (tmp)
	{
		if (tmp->type == E_HERDOC || tmp->type == E_REDIN)
			fd_in = tmp;
		else if (tmp->type == E_APPEND || tmp->type == E_REDOUT)
			fd_out = tmp;
		tmp = tmp->next;
	}
	if (fd_in)
		dup_in_fd(fd_in);
	if (fd_out)
		dup_out_fd(fd_out);
}
