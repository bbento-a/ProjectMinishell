/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbento-a <bbento-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:42:40 by mde-maga          #+#    #+#             */
/*   Updated: 2025/02/24 13:37:13 by bbento-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
char	**cmd_tab(t_token *start)
{
	t_token	*token;
	char	**tab;
	int		i;

	if (!start)
		return (NULL);
	token = start->next;
	i = 2;
	while (token && token->type < TRUNC)
	{
		token = token->next;
		i++;
	}
	if (!(tab = malloc(sizeof(char *) * i)))
		return (NULL);
	token = start->next;
	tab[0] = start->str;
	i = 1;
	while (token && token->type < TRUNC)
	{
		tab[i++] = token->str;
		token = token->next;
	}
	tab[i] = NULL;
	return (tab);
}

/// Replacing mini struct again, also commented the first if condition
/// because we can execute exit just like the other builtins.
/// Removed expansions

int	exec_cmd(t_command *command)
{
	char	**cmd;
	int		ret_val;

	cmd = command->args;
	// if (cmd && ft_strcmp(cmd[0], "exit") == 0 && has_pipe(token) == 0)
	// 	mini_exit(mini, cmd);
	if (cmd && is_builtin(cmd[0]))
		ret_val = exec_builtin(cmd);
	else if (cmd)
		ret_val = exec_bin(command, data()->env);
	free_tab(cmd);
/* 	ft_close(mini->pipein);
	ft_close(mini->pipeout);
	mini->pipein = -1;
	mini->pipeout = -1; */
	return (ret_val);
}