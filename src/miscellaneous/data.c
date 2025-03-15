/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbento-a <bbento-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 06:02:15 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/15 11:02:39 by bbento-a         ###   ########.fr       */
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
	new_env = NULL;
	if(!envp || !envp[0])
		return (new_env);
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

void	init_data(char **envp)
{
	data()->prompt_flag = true;
	data()->prompt = NULL;
	data()->cmds = NULL;
	data()->error_parse = false;
	data()->exit_code = 0;
	data()->last_exit_status = 0;
	data()->env = parse_envp(envp);
}

t_minishell	*data(void)
{
	static t_minishell	data;

	return (&data);
}
