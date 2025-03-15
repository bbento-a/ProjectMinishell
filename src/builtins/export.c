/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbento-a <bbento-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:23:13 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/15 08:15:01 by bbento-a         ###   ########.fr       */
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

static size_t	ft_strlen_equal(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

static int	search_env_variable(t_env *env, const char *var)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->value, var, ft_strlen_equal(var)) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(var);
			if (!tmp->value)
				return (display_err(NULL, NULL, "Failed to allocate memory",
						-1));
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
	tmp->next->value = ft_strdup(var);
	tmp->next->next = NULL;
	return (SUCCESS);
}

int	update_env(t_env **env, const char *var)
{
	if (!(*env))
	{
		*env = my_malloc(sizeof(t_env));
		if (!*env)
			return (display_err(NULL, NULL, "Failed to allocate memory", -1));
		(*env)->next = NULL;
		(*env)->value = ft_strdup(var);
		return (SUCCESS);
	}
	return (search_env_variable(*env, var));
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
