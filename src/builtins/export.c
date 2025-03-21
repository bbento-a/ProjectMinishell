/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbento-a <bbento-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:23:13 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/21 17:00:09 by bbento-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	print_error(char *arg)
{
	ft_putstr_fd("export: ", STDERR);
	ft_putstr_fd(arg, STDERR);
	ft_putstr_fd(": not a valid identifier", STDERR);
	ft_putstr_fd("\n", STDERR);
	data()->exit_code = 1;
	return (ERROR);
}

size_t	ft_strlen_equal(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

static int	search_env_variable(t_env *env, const char *name, const char *value)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->value, name, ft_strlen_equal(name)) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strjoin(name, "=");
			tmp->value = ft_strjoin(tmp->value, value);
			return (SUCCESS);
		}
		tmp = tmp->next;
	}
	tmp = env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = my_malloc(sizeof(t_env));
	if (!tmp->next)
		return (display_err(NULL, NULL, "Failed to allocate memory", -1));
	tmp->next->value = ft_strjoin(name, "=");
	tmp->next->value = ft_strjoin(tmp->next->value, value);
	tmp->next->next = NULL;
	return (SUCCESS);
}

int	update_env(t_env **env, const char *var)
{
	char	*equals_pos;
	char	*name;
	char	*value;

	// Find the position of '=' in the variable
	equals_pos = ft_strchr(var, '=');
	if (equals_pos)
	{
		// Split the variable into name and value
		name = ft_strndup(var, equals_pos - var);
		value = ft_strdup(equals_pos + 1);
		if (!*env)
		{
			*env = my_malloc(sizeof(t_env));
			(*env)->value = ft_strjoin(name, "=");
			(*env)->value = ft_strjoin((*env)->value, value);
			(*env)->next = NULL;
			free(name);
			free(value);
			return (SUCCESS);
		}
		else
			return (search_env_variable(*env, name, value));
	}
	return (ERROR);
}

int	ms_export(t_command *cmd, char **args)
{
	int	i;

	if (!args[1])
	{
		print_env(cmd, data()->env);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		if (!is_valid_env(args[i]))
			print_error(args[i]);
		else
		{
			if (update_env(&data()->env, args[i]) == -1)
				return (1);
		}
		i++;
	}
	if (data()->exit_code != 0)
		return (1);
	return (0);
}
