/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbento-a <bbento-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:54:21 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/15 02:19:49 by bbento-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	nb_args(char **args)
{
	int	size;

	size = 0;
	while (args[size])
		size++;
	return (size);
}

int	ms_echo(t_command *cmd, char **args)
{
	int	i;
	int	n_option;
	int fd_to;

	i = 1;
	n_option = 0;
	fd_to = look_for_fds(cmd);
	if (nb_args(args) > 1)
	{
		while (args[i] && ft_strncmp(args[i], "-n", 2) == 0)
		{
			n_option = 1;
			i++;
		}
		while (args[i])
		{
			ft_putstr_fd(args[i], fd_to);
			if (args[i + 1] && args[i][0] != '\0')
				ft_putchar_fd(' ', fd_to);
			i++;
		}
	}
	if (n_option == 0)
		ft_putchar_fd('\n', fd_to);
	if (fd_to != STDOUT)
		close(fd_to);
	return (SUCCESS);
}
