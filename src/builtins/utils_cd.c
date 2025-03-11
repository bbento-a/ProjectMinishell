/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbento-a <bbento-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:33:04 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/11 15:32:33 by bbento-a         ###   ########.fr       */
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

// Updates "PWD" env variable

int	update_pwd(t_env **env)
{
	char	cwd[PATH_MAX];
	char	*pwd;
	t_env	*tmp;

	tmp = *env;
	if (!getcwd(cwd, PATH_MAX))
		return (ERROR);
	while (tmp)
	{
		if (ft_strncmp(tmp->value, "PWD", 3) == 0)
		{
			pwd = ft_strjoin("PWD=", cwd);
			free(tmp->value);
			tmp->value = pwd;
			return (SUCCESS);
		}
		tmp = tmp->next;
	}
	pwd = ft_strjoin("PWD=", cwd);
	env_add(pwd, *env);
	return (SUCCESS);
}

// Updates "OLDPWD" env variable

int	update_oldpwd(t_env **env)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;
	t_env	*tmp;

	if (!getcwd(cwd, PATH_MAX))
		return (ERROR);
	tmp = *env;
	while (tmp) // iterates for env looking for OLDPWD
	{
		if (ft_strncmp(tmp->value, "OLDPWD", 6) == 0)
		{
			oldpwd = ft_strjoin("OLDPWD=", cwd);
			free(tmp->value);
			tmp->value = oldpwd;
			return (SUCCESS);
		}
		tmp = tmp->next;
	}
	oldpwd = ft_strjoin("OLDPWD=", cwd);
	env_add(oldpwd, *env);
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
