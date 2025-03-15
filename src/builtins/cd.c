/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbento-a <bbento-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:27:20 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/15 02:19:27 by bbento-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	go_to_path(int option, t_env *env)
{
	char	*env_path;

	env_path = NULL;
	if (option == 0) // Go to HOME
	{
		if (!(env_path = get_env_path(env, "HOME=", 5)))
			return (display_err("minishell: cd: ", NULL, "HOME not set", 1));
	}
	else if (option == 1) // Go to OLDPWD
	{
		if (!(env_path = get_env_path(env, "OLDPWD=", 7)))
			return (display_err("minishell: cd: ", NULL, "OLDPWD not set", 1));
		ft_putendl_fd(env_path, STDOUT); // Print OLDPWD path
	}
	update_oldpwd(&data()->env);
	if (chdir(env_path) < 0)
		return (ft_memdel((void **)&env_path), ERROR);
	update_pwd(&data()->env);
	ft_memdel((void **)&env_path);
	return (SUCCESS);
}

int	ms_cd(char **args, t_env *env)
{
	if (!args[1])
		return (go_to_path(0, env)); // No argument -> Go to HOME
	if (args[2])
		return (display_err("minishell: cd: ", NULL, "too many arguments", 1));
	if (ft_strncmp(args[1], "-", 1) == 0)
		return (go_to_path(1, env)); // Argument "-" -> Go to OLDPWD
	update_oldpwd(&data()->env); // Update OLDPWD
	if (chdir(args[1]) < 0)
		return (display_err("minishell: cd: ", NULL, "No such file or directory", 1));
	update_pwd(&data()->env);
	return (SUCCESS);
}
