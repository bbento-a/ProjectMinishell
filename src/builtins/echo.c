/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbento-a <bbento-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:54:21 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/15 04:04:55 by bbento-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	new_line_flag(char **args, int *new_line)
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		j = 0;
		if (args[i][j++] == '-')
		{
			while (args[i][j] && args[i][j] == 'n')
				j++;
			if (args[i][j] && args[i][j] != 'n')
				return (i);
			*new_line = 0;
		}
		else
			return (i);
		i++;
	}
	return (i);
}

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
	int	fd_to;
	int	i;
	int	nl;

	nl = 1;
	fd_to = look_for_fds(cmd);
	i = new_line_flag(args, &nl);
	if (nb_args(args) > 1)
	{
		while (args[i])
		{
			ft_putstr_fd(args[i], fd_to);
			if (args[i + 1] && args[i][0] != '\0')
				ft_putchar_fd(' ', fd_to);
			i++;
		}
	}
	if (nl == 1)
		ft_putchar_fd('\n', fd_to);
	if (fd_to != STDOUT)
		close(fd_to);
	return (SUCCESS);
}
