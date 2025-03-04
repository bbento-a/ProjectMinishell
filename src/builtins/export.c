/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbento-a <bbento-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:23:13 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/04 18:26:44 by bbento-a         ###   ########.fr       */
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

size_t ft_strlen_equal(const char *str)
{
	int i;

	i = 0;
	while(str[i] && str[i] != '=')	
		i++;
	return (i);
}

static int	update_env(t_env **env, const char *var)
{
	t_env	*tmp;

	// If there is no env to begin with
	if(!(*env))
	{
		*env = malloc(sizeof(t_env));
		if (!*env)
			return (-1);
		(*env)->next = NULL;
		(*env)->value = ft_strdup(var);
		return (SUCCESS);
	}
	tmp = *env;
	// Search for the variable in the environment
	while (tmp)
	{
		// Check if the variable already exists, update if found
		if (ft_strncmp(tmp->value, var, ft_strlen_equal(var)) == 0) // WIP
		{
			ft_memdel((void **)&tmp);
			tmp->value = ft_strdup(var);
			return (SUCCESS);
		}
		tmp = tmp->next;
	}
	// If not found, add a new entry to the environment list
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = malloc(sizeof(t_env));
	if (!tmp->next)
		return (-1);
	tmp->next->value = ft_strdup(var);
	tmp->next->next = NULL;
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
	i = 1;
	// Iterate through arguments and process them
	while (cmd[i])
	{
		if (!is_valid_env(cmd[i])) // Check if the variable is valid
		{
			print_error(cmd[i], ": not a valid identifier");
			return (1);
		}
		// Add or update the environment variable
		if (update_env(&data()->env, cmd[i]) == -1)
			return (1);
		i++;
	}
	return (0);
}
