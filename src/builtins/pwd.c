/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbento-a <bbento-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:11:18 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/15 08:15:12 by bbento-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ms_pwd(t_command *cmd)
{
	char	cwd[PATH_MAX];
	int		fd_to;

	fd_to = look_for_fds(cmd);
	if (getcwd(cwd, PATH_MAX))
	{
		ft_putendl_fd(cwd, fd_to);
		return (SUCCESS);
	}
	else
		return (display_err("minishell: pwd:", NULL,
				"Unable to get current working directory", 1));
}
