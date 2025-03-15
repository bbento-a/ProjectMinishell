/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mtmpfb@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:09:00 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/15 07:32:39 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env	*parse_envp(char **envp)
{
	t_env	*new_env;
	t_env	*tmp;
	t_env	*last_node;
	int		i;

	i = 0;
	while (envp[i])
	{
		tmp = my_malloc(sizeof(t_env));
		tmp->value = ft_strdup(envp[i]);
		tmp->envp = &envp[i];
		tmp->next = NULL;
		if (i == 0)
			new_env = tmp;
		else
			last_node->next = tmp;
		last_node = tmp;
		i++;
	}
	return (new_env);
}
