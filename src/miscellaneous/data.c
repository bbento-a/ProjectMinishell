/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbento-a <bbento-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 02:30:08 by bbento-a          #+#    #+#             */
/*   Updated: 2025/03/15 02:44:36 by bbento-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env *parse_envp(char **envp)
{
    t_env *new_env;
    t_env *tmp;
    t_env *last_node;
    int i = 0;

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


// Initiates the variables so we're not working wiith uninitialized values

void	init_data(char **envp)
{
	data()->prompt_flag = true;
	data()->prompt = NULL;
	data()->cmds = NULL;
	data()->error_parse = false;
	data()->exit_code = 0;
	data()->last_exit_status = 0;
	data()->env = parse_envp(envp);
	// data()->shlvl = expand_token("SHLVL");
}

// Stores data that will be needed to identify things for the parsing

t_minishell	*data(void)
{
	static t_minishell	data;

	return (&data);
}
