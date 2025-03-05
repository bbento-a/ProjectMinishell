/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbento-a <bbento-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:37:59 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/05 15:27:54 by bbento-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	if (ft_strlen(s1) != ft_strlen(s2))
		return (1);
	while (s1[i] && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}
int	is_builtin(char *command)
{
	if (!command)
		return (0);
	if (ft_strcmp(command, "echo") == 0)
		return (1);
	else if (ft_strcmp(command, "cd") == 0)
		return (1);
	else if (ft_strcmp(command, "pwd") == 0)
		return (1);
	else if (ft_strcmp(command, "env") == 0)
		return (1);
	else if (ft_strcmp(command, "export") == 0)
		return (1);
	else if (ft_strcmp(command, "unset") == 0)
		return (1);
	else if (ft_strcmp(command, "exit") == 0)
		return (1);
	else
		return (0);
}

int	exec_builtin(char **args)
{
	if (ft_strcmp(args[0], "echo") == 0)
		return (ms_echo(args));
	else if (ft_strcmp(args[0], "cd") == 0)
		return (ms_cd(args, data()->env));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (ms_pwd());
	else if (ft_strcmp(args[0], "env") == 0)
		return (ms_env(data()->env));
	else if (ft_strcmp(args[0], "export") == 0)
		return (ms_export(args));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (ms_unset(args));
	else if (ft_strcmp(args[0], "exit") == 0)
		return (builtin_exit(args));
	return (0);
}
