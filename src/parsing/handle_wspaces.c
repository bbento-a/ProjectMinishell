/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_wspaces.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mtmpfb@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 07:39:22 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/15 07:39:27 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	clear_next_node(t_line *current)
{
	t_line	*tmp;

	tmp = current->next;
	current->next = tmp->next;
	if (tmp->next)
		tmp->next->prev = current;
	free(tmp);
}

static int	join_arguments(t_line *current, t_line *next)
{
	char	*res;

	res = ft_strjoin(current->content, next->content);
	if (!res)
		return (display_err(NULL, NULL, "Failed to join node contents", 1));
	free(current->content);
	free(next->content);
	if (current->type_q == '0' && next->type_q != '0')
		current->type_q = next->type_q;
	current->content = res;
	return (0);
}

int	handle_wspaces(t_line *prompt)
{
	while (prompt)
	{
		if (prompt->next && prompt->next->white_space == false)
		{
			if ((prompt->type_n < E_OTHER) || (prompt->next
					&& prompt->next->type_n < E_OTHER))
			{
				prompt = prompt->next;
				continue ;
			}
			else
			{
				if (join_arguments(prompt, prompt->next))
					return (1);
				clear_next_node(prompt);
				continue ;
			}
		}
		if (prompt)
			prompt = prompt->next;
	}
	return (0);
}
