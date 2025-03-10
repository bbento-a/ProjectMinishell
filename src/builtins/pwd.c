/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-maga <mtmpfb@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:11:18 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/10 16:38:32 by mde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
// update
int	ms_pwd(t_command *cmd)
{
	char cwd[PATH_MAX];
	int fd_to;

	fd_to = look_for_fds(cmd);
	if (getcwd(cwd, PATH_MAX))
	{
		ft_putendl_fd(cwd, fd_to); // Print current working directory
		return (SUCCESS);           // Return success code
	}
	else
	{
		ft_putstr_fd("Error: Unable to get current working directory\n",
			STDERR);
		return (ERROR); // Return error code
	}
}