/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbento-a <bbento-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:54:39 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/15 04:41:47 by bbento-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_in_env(t_env *env, const char *var)
{
	while (env)
	{
		if (ft_strncmp(env->value, var, ft_strlen(var)) == 0)
			return (1); // Found the variable in the environment
		env = env->next;
	}
	return (0); // Variable not found in the environment
}

int	is_valid_env(const char *s)
{
	int	i;

	i = 0;
	// Check that the first character is a valid start of an identifier (letter or underscore)
	if (!(ft_isalpha(s[i]) || s[i] == '_'))
		return (0);
	i++;
	// Check that the rest of the characters are valid (alphanumeric or underscore)
	while (s[i] != '=' && s[i])
	{
		if (!(ft_isalnum(s[i]) || s[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

void	print_env(t_command *cmd, t_env *env)
{
	int	fd_to;

	fd_to = look_for_fds(cmd);
	while (env)
	{
		ft_putstr_fd("declare -x ", fd_to);
		ft_putstr_fd(env->value, fd_to);
		if (ft_strchr(env->value, '='))
		{
			ft_putstr_fd("=\"", fd_to);
			ft_putstr_fd(env->value, fd_to);
			ft_putstr_fd("\"\n", fd_to);
		}
		else
			ft_putstr_fd("\n", fd_to);
		env = env->next;
	}
}

int	ms_env(t_command *cmd, t_env *env)
{
	int	fd_to;

	fd_to = look_for_fds(cmd);
	while (env)
	{
		if (ft_strchr(env->value, '=') != NULL)
		// Check if '=' exists in the string
		{
			ft_putstr_fd(env->value, fd_to); // Print the variable
			ft_putstr_fd("\n", fd_to);
		}
		env = env->next; // Move to the next node
	}
	return (0);
}
