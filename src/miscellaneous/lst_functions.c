/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbento-a <bbento-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 02:49:44 by bbento-a          #+#    #+#             */
/*   Updated: 2025/03/15 02:49:51 by bbento-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Auxiliar func. for the lexer

t_line	*find_lastnode(t_line *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

// Defines quoted nodes in lexer

void	define_flg(char c)
{
	if (c == '\'')
		data()->hld_flag = '\'';
	else if (c == '\"')
		data()->hld_flag = '\"';
	else
		data()->hld_flag = '0';
}

void	clear_linelst(t_line **lst)
{
	t_line	*tmp;

	if (!*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		if ((*lst)->content)
			free((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
	lst = NULL;
}
// Defines node type

t_type	define_type(t_line *node)
{
	int		i;

	i = 0;
	if (node->type_q != '0')
		return (node->type_n = E_OTHER);
	else if (node->content[i] == '>' && node->content[i + 1] == '>'
		&& node->content[i + 2] == '\0')
		return (node->type_n = E_APPEND);
	else if (node->content[i] == '<' && node->content[i + 1] == '<'
		&& node->content[i + 2] == '\0')
		return (node->type_n = E_HERDOC);
	else if (node->content[i] == '>' && node->content[i + 1] == '\0')
		return (node->type_n = E_REDOUT);
	else if (node->content[i] == '<' && node->content[i + 1] == '\0')
		return (node->type_n = E_REDIN);
	else if (node->content[i] == '|' && node->content[i + 1] == '\0')
		return (node->type_n = E_PIPE);
	else
		return (node->type_n = E_OTHER);
}
// Defines white spaces befores the contents on the input line

void	define_white_space(t_line *node, char *line, int bgn)
{
	node->white_space = false;
	if (!node->prev)
		return ;
	else if (node->type_q != '0')
	{
		if (line[bgn - 2] == ' ' || line[bgn - 2] == '\t')
			node->white_space = true;
	}
	else
	{
		if (line[bgn - 1] == ' ' || line[bgn - 1] == '\t')
			node->white_space = true;
	}
}
