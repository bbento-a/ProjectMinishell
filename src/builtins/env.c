/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbento-a <bbento-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:54:39 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/21 16:59:38 by bbento-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_in_env(t_env *env, const char *var)
{
	while (env)
	{
		if (ft_strncmp(env->value, var, ft_strlen(var)) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

int	is_valid_env(const char *s)
{
	int	i;

	i = 0;
	if (!(ft_isalpha(s[i]) || s[i] == '_'))
		return (0);
	i++;
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
	int		fd_to;
	char	*equals_pos;
	size_t	name_len;

	fd_to = look_for_fds(cmd);
	while (env)
	{
		ft_putstr_fd("declare -x ", fd_to);
		equals_pos = ft_strchr(env->value, '=');
		if (equals_pos)
		{
			name_len = equals_pos - env->value;
			write(fd_to, env->value, name_len);
			ft_putstr_fd("=\"", fd_to);
			ft_putstr_fd(equals_pos + 1, fd_to);
			ft_putstr_fd("\"\n", fd_to);
		}
		else
		{
			ft_putstr_fd(env->value, fd_to);
			ft_putstr_fd("\n", fd_to);
		}
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
		{
			ft_putstr_fd(env->value, fd_to);
			ft_putstr_fd("\n", fd_to);
		}
		env = env->next;
	}
	return (0);
}
