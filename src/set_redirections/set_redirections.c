#include "../../inc/minishell.h"

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
		if (quotes == true)
			line = expand_token(line);
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
	close(write_fd);
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
	{
		close(fd[0]);
		heredoc_signals();
		heredocument_loop(fd[1], limiter, quotes);
		clear_memory(data()->cmds);
		clear_env(data()->env);
		close(fd[1]);
		exit(0);
	}
	else
	{
		close(fd[1]);
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status))
			data()->exit_code = status;
	}
	// child needs condition to catch signal (global)
	// child clears all memo from cmds
	// main waits from child (heredoc) to finish
	// return(the read part of the pipe);
	return (fd[0]);
}

int	redirection_validation(t_files *file)
{
	int	fd;

	if (!file)
		return (-1);
	else if (file->type == E_REDIN)
		fd = open(file->file_name, O_RDONLY);
	else if (file->type == E_REDOUT)
		fd = open(file->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (file->type == E_APPEND)
		fd = open(file->file_name, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd == -1)
		return (display_err("minishell", file->file_name,
				"No such file or directory", 1));
	close(fd);
	return (0);
}
int	heredoc_validation(t_files *file)
{
	int	fd;

	fd = heredocument(file->file_name, file->hq_limiter);
	if (data()->error_parse)
	{
		close(fd);
		return (1);
	}
	file->fd = fd;
	return (0);
}

int	check_heredocs(t_files *files)
{
	t_files	*tmp;

	tmp = files;
	while (tmp)
	{
		if (tmp->type == E_HERDOC && heredoc_validation(tmp))
			return (1); // turns command invalid, it doesn't even need to build it's path
		tmp = tmp->next;
	}
	return (0);
}

int	check_command_redirections(t_files *files)
{
	t_files	*tmp;

	tmp = files;
	while (tmp)
	{
		if (tmp->type != E_HERDOC && redirection_validation(tmp))
			return (1); // turns command invalid, it doesn't even need to build it's path
		tmp = tmp->next;
	}
	return (0);
}

int	check_redirections(t_command *cmds)
{
	t_command	*cmd;

	cmd = cmds;
	while (cmd)
	{
		check_heredocs(cmd->files);
		if (data()->error_parse)
			return (1);
		cmd = cmd->next;
	}
	cmd = cmds;
	while (cmd)
	{
		check_command_redirections(cmd->files);
		cmd = cmd->next;
	}
	return (0);
}
