/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbento-a <bbento-a@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 02:47:22 by bbento-a          #+#    #+#             */
/*   Updated: 2025/03/15 07:35:55 by bbento-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void write_to_heredoc(int write_fd, bool quotes, char *line)
{
	if (quotes == true)
		line = expand_token(line);
	write(write_fd, line, ft_strlen(line));
	write(write_fd, "\n", 1);
	free(line);
}

void	heredocument_loop(int write_fd, char *limit, bool quotes)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline("\t>");
		if (data()->error_parse)
		{
			free(line);
			break ;
		}
		if (!line)
		{
			display_err("\nMinishell: heredoc", NULL, "Expecting delimiter", 0);
			break ;
		}
		else if (ft_strlen(limit) == ft_strlen(line) && ft_strncmp(line, limit,
				ft_strlen(limit)) == 0 && !line[ft_strlen(limit)])
		{
			free(line);
			break ;
		}
		write_to_heredoc(write_fd, quotes, line);
	}
	close(write_fd);
}

int	execute_heredoc(char *limiter, bool quotes, int *fd)
{
	close(fd[0]);
	heredoc_signals();
	heredocument_loop(fd[1], limiter, quotes);
	clear_memory(data()->cmds);
	clear_env(data()->env);
	close(fd[1]);
	exit(0);
}

int	heredocument(char *limiter, bool quotes)
{
	pid_t	pid;
	int		fd[2];
	int		status;

	if (pipe(fd) == -1)
		return (display_err(NULL, NULL, "Failed to create pipe", 1));
	pid = fork();
	if (pid == -1)
		return (display_err(NULL, NULL, "Failed to fork process", 1));
	else if (pid == 0)
		execute_heredoc(limiter, quotes, fd);
	else
	{
		close(fd[1]);
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status))
		{
			write(1, "\n", 1);
			data()->exit_code = status;
			data()->error_parse = true;
		}
	}
	return (fd[0]);
}
