/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mtmpfb@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:23:13 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/23 17:35:25 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	search_env_variable(t_env *env, const char *name, const char *value)
{
	t_env	*tmp;
	char	*new_value;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->value, name, ft_strlen_equal(name)) == 0)
		{
			free(tmp->value);
			if (value)
			{
				new_value = ft_strjoin(name, "=");
				tmp->value = ft_strjoin(new_value, value);
				free(new_value);
			}
			else
				tmp->value = ft_strdup(name);
			return (SUCCESS);
		}
		tmp = tmp->next;
	}
	return (append_new_env(env, name, value));
}

int	init_env(t_env **env, char *name, char *value)
{
	char	*tmp;

	*env = my_malloc(sizeof(t_env));
	if (!*env)
		return (ERROR);
	if (value)
		(*env)->value = ft_strjoin(name, "=");
	else
		(*env)->value = ft_strdup(name);
	if (value)
	{
		tmp = (*env)->value;
		(*env)->value = ft_strjoin(tmp, value);
		free(tmp);
	}
	(*env)->next = NULL;
	return (SUCCESS);
}

int	parse_env(const char *var, char **name, char **value)
{
	char	*equals_pos;

	equals_pos = ft_strchr(var, '=');
	if (equals_pos)
	{
		*name = ft_strndup(var, equals_pos - var);
		*value = ft_strdup(equals_pos + 1);
	}
	else
	{
		*name = ft_strdup(var);
		*value = NULL;
	}
	if (!*name)
		return (ERROR);
	return (SUCCESS);
}

int	update_env(t_env **env, const char *var)
{
	char	*name;
	char	*value;
	int		result;

	if (parse_env(var, &name, &value) == ERROR)
		return (ERROR);
	if (!*env)
	{
		result = init_env(env, name, value);
		free(name);
		if (value)
			free(value);
		return (result);
	}
	result = search_env_variable(*env, name, value);
	free(name);
	if (value)
		free(value);
	return (result);
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
		else if (update_env(&data()->env, args[i]) == -1)
			return (1);
		i++;
	}
	if (data()->exit_code != 0)
		return (1);
	return (0);
}
