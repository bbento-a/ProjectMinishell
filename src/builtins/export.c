/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbento-a <bbento-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:23:13 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/04 15:34:26 by bbento-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	print_error(char *arg, char *msg)
{
	ft_putstr_fd("export: not a valid identifier: ", STDERR);
	ft_putstr_fd(arg, STDERR);
	ft_putstr_fd(msg, STDERR);
	ft_putstr_fd("\n", STDERR);
	return (ERROR);
}

static int	is_valid_env(const char *s)
{
	int	i;

	i = 0;
	// Check that the first character is a valid start of an identifier (letter or underscore)
	if (!(ft_isalpha(s[i]) || s[i] == '_'))
		return (0);
	// Check that the rest of the characters are valid (alphanumeric or underscore)
	while (s[++i])
	{
		if (!(ft_isalnum(s[i]) || s[i] == '_'))
			return (0);
	}
	return (1);
}

static int	update_env(t_env *env, const char *var)
{
	t_env	*tmp;

	// Search for the variable in the environment
	while (env)
	{
		// Check if the variable already exists, update if found
		if (ft_strncmp(env->value, var, ft_strlen(var)) == 0)
		{
			ft_memdel((void **)&env->value);
			env->value = ft_strdup(var);
			return (SUCCESS);
		}
		env = env->next;
	}
	// If not found, add a new entry to the environment list
	if (!(tmp = malloc(sizeof(t_env))))
		return (-1);
	tmp->value = ft_strdup(var);
	tmp->next = env;
	return (SUCCESS);
}

static void	print_env(t_env *env)
{
	while (env)
	{
		ft_putstr_fd("declare -x ", STDOUT);
		ft_putstr_fd(env->value, STDOUT);
		if (ft_strchr(env->value, '='))
		{
			ft_putstr_fd("=\"", STDOUT);
			ft_putstr_fd(env->value, STDOUT);
			ft_putstr_fd("\"\n", STDOUT);
		}
		else
			ft_putstr_fd("\n", STDOUT);
		env = env->next;
	}
}
/// Changed return values
/// mini->env is now from the data so it doesn't depend on mini structure

int	ms_export(char **cmd)
{
	int	i;

	// If no arguments, print the sorted environment
	if (!cmd[1])
	{
		print_env(data()->env);
		return (0);
	}
	// Iterate through arguments and process them
	for (i = 1; cmd[i]; i++)
	{
		if (!is_valid_env(cmd[i])) // Check if the variable is valid
		{
			print_error(cmd[i], ": not a valid identifier");
			return (1);
		}
		// Add or update the environment variable
		if (update_env(data()->env, cmd[i]) == -1)
			return (1);
	}
	return (0);
}
