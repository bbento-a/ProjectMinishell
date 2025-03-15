/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_expan.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mtmpfb@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 07:42:28 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/15 07:43:29 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	remove_expanded_node(t_line **head, t_line *node)
{
	t_line	*tmp;

	if (!node->prev)
	{
		tmp = (*head);
		*head = (*head)->next;
		free(tmp->content);
		free(tmp);
		if (*head)
			(*head)->prev = NULL;
	}
}

int	expansion_analyzer(t_line **input, t_line *prompt)
{
	int	i;

	i = 0;
	while (prompt->content[i])
	{
		if (prompt->content[i] == '$' && prompt->content[i + 1]
			&& (ft_isalnum(prompt->content[i + 1]) || prompt->content[i
					+ 1] == '_' || prompt->content[i + 1] == '?'))
		{
			prompt->content = expand_token(prompt->content);
			break ;
		}
		else if (prompt->content[i] == '$' && prompt->next
			&& (prompt->next->type_q == '\"' || prompt->next->type_q == '\''))
		{
			prompt->content = replace_var(prompt->content, ft_strdup(""), i, 0);
			break ;
		}
		if (!prompt->content[i])
			break ;
		i++;
	}
	if (!prompt->content[0] && !prompt->prev)
	{
		remove_expanded_node(input, prompt);
		return (1);
	}
	return (0);
}

int	search_expansion(t_line **input)
{
	t_line	*prompt;
	t_line	*tmp;

	prompt = *input;
	while (prompt)
	{
		if (prompt->prev && prompt->prev->type_n == E_HERDOC)
		{
			prompt = prompt->next;
			continue ;
		}
		if (prompt->type_q != '\'')
		{
			tmp = prompt->next;
			if (expansion_analyzer(input, prompt))
			{
				prompt = tmp;
				continue ;
			}
		}
		if (prompt->type_q != '\'' && prompt->type_q != '\"')
		{
			tmp = prompt->next;
			if (handle_post_expansion(input, prompt))
				return (1);
			prompt = tmp;
			continue ;
		}
		prompt = prompt->next;
	}
	return (0);
}
