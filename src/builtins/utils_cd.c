/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbento-a <bbento-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:33:04 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/04 15:34:10 by bbento-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_env_path(t_env *env, const char *var, size_t len)
{
	while (env)
	{
		if (ft_strncmp(env->value, var, len) == 0)
			return (ft_strdup(env->value + len));
		env = env->next;
	}
	return (NULL);
}

int	update_oldpwd(t_env *env)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;

	if (!getcwd(cwd, PATH_MAX))
		return (ERROR);
	oldpwd = ft_strjoin("OLDPWD=", cwd);
	if (!oldpwd)
		return (ERROR);
	if (!is_in_env(env, oldpwd))
		env_add(oldpwd, env);
	ft_memdel((void **)&oldpwd);
	return (SUCCESS);
}

void	ft_memdel(void **ap)
{
	if (ap && *ap)
	{
		free(*ap);  // Free the memory pointed to by *ap
		*ap = NULL; // Set the pointer to NULL to avoid dangling references
	}
}

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

void	env_add(char *var, t_env *env)
{
	t_env	*new_env;

	new_env = malloc(sizeof(t_env));
	if (!new_env)
		return ; // Allocation failed
	new_env->value = ft_strdup(var); // Assuming ft_strdup is your custom strdup
	if (!new_env->value)
	{
		free(new_env); // If strdup fails, free the new env node
		return ;
	}
	new_env->next = env;
	env = new_env; // Add the new node at the front of the list
}
