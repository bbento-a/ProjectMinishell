/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbento-a <bbento-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:54:21 by mde-maga          #+#    #+#             */
/*   Updated: 2025/03/06 17:35:12 by bbento-a         ###   ########.fr       */
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

/* int	ft_strcmp(char *s1, char *s2) // Matches header
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

void	ft_putstr_fd(char *s, int fd) // Matches header
{
	if (s)
		write(fd, s, strlen(s));
}

// Main function
int	main(int argc, char **argv)
{
	// Pass the command-line arguments to ms_echo
	if (argc > 1)
		ms_echo(argv);
	else
		write(1, "\n", 1); // If no arguments are passed, just output a newline

	return (SUCCESS);
} */
