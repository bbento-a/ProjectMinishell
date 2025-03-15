/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbento-a <bbento-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 06:03:41 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/15 10:51:21 by bbento-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_files(t_files *files)
{
	t_files	*tmp;

	if (!files)
		return ;
	while (files)
	{
		tmp = files;
		files = files->next;
		if (tmp->type == E_HERDOC && access(tmp->file_name, F_OK) == 0
			&& unlink(tmp->file_name) == -1)
			display_err(NULL, tmp->file_name, "Error removing heredoc file", 1);
		free(tmp->file_name);
		free(tmp);
	}
}

void	free_cmds(t_command **cmds)
{
	t_command	*tmp;

	if (!cmds)
		return ;
	while (*cmds)
	{
		tmp = (*cmds)->next;
		if ((*cmds)->args)
			free((*cmds)->args);
		free_files((*cmds)->files);
		free(*cmds);
		*cmds = tmp;
	}
	cmds = NULL;
}

void	free_array(char **mtx)
{
	int	i;

	i = 0;
	if (!mtx)
		return ;
	while (mtx[i])
	{
		if (*mtx)
			free(mtx[i]);
		i++;
	}
	free(mtx);
	mtx = NULL;
}
