/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbento-a <bbento-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:54:39 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/15 02:20:05 by bbento-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ms_env(t_command *cmd, t_env *env)
{
	int fd_to;

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
