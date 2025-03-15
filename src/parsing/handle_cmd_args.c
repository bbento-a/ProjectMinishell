/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mtmpfb@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 07:36:56 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/15 07:37:08 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	handle_node_args(t_line *bgn, t_line *last)
{
	int	nb;

	nb = 0;
	while (bgn != last->next)
	{
		if (bgn->type_n < E_PIPE)
			bgn = bgn->next;
		else if (bgn->type_n != E_PIPE)
		{
			nb++;
			bgn->arg = true;
		}
		if (bgn == last)
			break ;
		bgn = bgn->next;
	}
	return (nb);
}

void	make_cmd_args(char **args, t_line *bgn, t_line *last, int size)
{
	int	i;

	i = 0;
	(void)last;
	while (i < size && bgn != last->next)
	{
		if (bgn->arg == true)
		{
			args[i] = ft_strdup(bgn->content);
			i++;
		}
		bgn = bgn->next;
	}
	args[size] = NULL;
}
