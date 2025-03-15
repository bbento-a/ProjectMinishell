/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_list_nodes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mtmpfb@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 07:37:42 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/15 07:38:18 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	add_cmds_last(t_command **cmds, t_command *node)
{
	t_command	*temp;

	if (!(*cmds))
	{
		*cmds = node;
		return ;
	}
	temp = *cmds;
	while (temp && temp->next)
		temp = temp->next;
	temp->next = node;
	node->previous = temp;
}

t_files	*create_file_node(t_line *node, t_type redir)
{
	t_files	*file;

	file = my_malloc(sizeof(t_files));
	if (!file)
	{
		display_err(NULL, NULL, "Failed to allocate file node", 1);
		return (NULL);
	}
	file->file_name = ft_strdup(node->content);
	file->fd = -1;
	file->hq_limiter = 0;
	if (node->type_q == '0' && redir == E_HERDOC)
		file->hq_limiter = 1;
	file->type = redir;
	file->previous = NULL;
	file->next = NULL;
	return (file);
}

void	add_files_to_list(t_files **lst, t_files *file)
{
	t_files	*tmp;

	tmp = *lst;
	if (!(*lst))
	{
		*lst = file;
		return ;
	}
	while (tmp && tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = file;
	file->previous = tmp;
}

t_files	*make_cmd_files(t_line *bgn, t_line *last)
{
	t_files	*files;
	t_files	*node;

	files = NULL;
	while (bgn != last)
	{
		node = NULL;
		if (bgn->type_n < E_PIPE)
		{
			node = create_file_node(bgn->next, bgn->type_n);
			add_files_to_list(&files, node);
		}
		bgn = bgn->next;
	}
	return (files);
}
